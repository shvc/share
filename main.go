package main

import (
	"bufio"
	"flag"
	"fmt"
	"io"
	"log"
	"net"
	"net/http"
	"os"
	"os/user"
	"path/filepath"
	"strconv"
	"strings"
	"time"

	"golang.org/x/crypto/ssh"
	"golang.org/x/crypto/ssh/agent"
	"golang.org/x/crypto/ssh/knownhosts"
	"golang.org/x/term"
)

func main() {
	listenAddr := flag.String("l", "0.0.0.0:8888", "本地代理监听地址 (同时服务 SOCKS5 与 HTTP)")
	identity := flag.String("i", "", "私钥文件路径 (可逗号分隔多个)")
	password := flag.String("p", "", "登录密码 (可选;不填则需要时交互式输入)")
	insecure := flag.Bool("insecure", false, "跳过 known_hosts 校验")
	flag.Usage = func() {
		fmt.Fprintln(os.Stderr, "用法: gossh [-l listen] [-i key] [-p password] [-insecure] user@host[:port]")
		flag.PrintDefaults()
	}
	flag.Parse()

	if flag.NArg() != 1 {
		flag.Usage()
		os.Exit(2)
	}
	userName, host, port, err := parseTarget(flag.Arg(0))
	if err != nil {
		log.Fatalf("解析目标地址失败: %v", err)
	}

	cfg, err := buildSSHConfig(userName, host, *identity, *password, *insecure)
	if err != nil {
		log.Fatalf("构建 SSH 配置失败: %v", err)
	}

	sshAddr := net.JoinHostPort(host, strconv.Itoa(port))
	log.Printf("正在连接 SSH: %s@%s ...", userName, sshAddr)
	client, err := ssh.Dial("tcp", sshAddr, cfg)
	if err != nil {
		log.Fatalf("SSH 连接失败: %v", err)
	}
	defer client.Close()
	log.Printf("SSH 连接已建立")

	go keepAlive(client)

	ln, err := net.Listen("tcp", *listenAddr)
	if err != nil {
		log.Fatalf("监听 %s 失败: %v", *listenAddr, err)
	}
	defer ln.Close()
	log.Printf("代理监听中: %s (同时支持 SOCKS5 / HTTP)", *listenAddr)

	for {
		c, err := ln.Accept()
		if err != nil {
			log.Printf("accept 失败: %v", err)
			continue
		}
		go handleConn(c, client)
	}
}

// ---------- 目标地址解析 ----------

// parseTarget 解析 "[user@]host[:port]",port 缺省为 22。
// 支持 IPv6 字面量,如 user@[::1]:22。
func parseTarget(s string) (userName, host string, port int, err error) {
	port = 22
	if i := strings.IndexByte(s, '@'); i >= 0 {
		userName, s = s[:i], s[i+1:]
	} else {
		userName = currentUserName()
	}
	if userName == "" {
		return "", "", 0, fmt.Errorf("无法确定用户名,请使用 user@host 形式")
	}
	// 尝试 host:port (含 IPv6 [::1]:port);失败则视为纯 host
	if h, p, e := net.SplitHostPort(s); e == nil {
		host = h
		if port, err = strconv.Atoi(p); err != nil {
			return "", "", 0, fmt.Errorf("非法端口 %q: %w", p, err)
		}
	} else {
		host = strings.Trim(s, "[]")
	}
	if host == "" {
		return "", "", 0, fmt.Errorf("缺少 host")
	}
	return userName, host, port, nil
}

func currentUserName() string {
	if u, err := user.Current(); err == nil {
		return u.Username
	}
	return os.Getenv("USER")
}

// ---------- SSH 配置 ----------

func buildSSHConfig(userName, host, identity, password string, insecure bool) (*ssh.ClientConfig, error) {
	var auths []ssh.AuthMethod
	var loaded []string

	// 1) ssh-agent (公钥)
	if sock := os.Getenv("SSH_AUTH_SOCK"); sock != "" {
		if conn, err := net.Dial("unix", sock); err == nil {
			auths = append(auths, ssh.PublicKeysCallback(agent.NewClient(conn).Signers))
			loaded = append(loaded, "ssh-agent")
		}
	}

	// 2) 私钥文件 (公钥)
	var keyFiles []string
	if identity != "" {
		keyFiles = strings.Split(identity, ",")
	} else {
		home, _ := os.UserHomeDir()
		for _, name := range []string{"id_ed25519", "id_ecdsa", "id_rsa"} {
			keyFiles = append(keyFiles, filepath.Join(home, ".ssh", name))
		}
	}
	for _, kf := range keyFiles {
		kf = strings.TrimSpace(kf)
		if kf == "" {
			continue
		}
		data, err := os.ReadFile(kf)
		if err != nil {
			continue
		}
		signer, err := ssh.ParsePrivateKey(data)
		if err != nil {
			if _, ok := err.(*ssh.PassphraseMissingError); ok {
				fmt.Fprintf(os.Stderr, "私钥 %s 已加密,请输入 passphrase: ", kf)
				pp, perr := term.ReadPassword(int(os.Stdin.Fd()))
				fmt.Fprintln(os.Stderr)
				if perr == nil {
					if s, e := ssh.ParsePrivateKeyWithPassphrase(data, pp); e == nil {
						signer = s
					}
				}
			}
			if signer == nil {
				continue
			}
		}
		auths = append(auths, ssh.PublicKeys(signer))
		loaded = append(loaded, "key:"+kf)
	}

	// 3) 密码 —— 与私钥并存,服务端拒掉公钥后会自动回退到密码
	if password != "" {
		auths = append(auths, ssh.Password(password))
		loaded = append(loaded, "password(cli)")
	} else {
		// 交互式:只在服务端真的请求密码时才提示
		auths = append(auths, ssh.PasswordCallback(func() (string, error) {
			fmt.Fprintf(os.Stderr, "%s@%s 的密码: ", userName, host)
			pp, err := term.ReadPassword(int(os.Stdin.Fd()))
			fmt.Fprintln(os.Stderr)
			return string(pp), err
		}))
		// 同时支持 keyboard-interactive (某些服务器只开这个)
		auths = append(auths, ssh.KeyboardInteractive(func(name, instr string, qs []string, echos []bool) ([]string, error) {
			answers := make([]string, len(qs))
			for i, q := range qs {
				fmt.Fprintf(os.Stderr, "%s", q)
				if echos[i] {
					r := bufio.NewReader(os.Stdin)
					line, _ := r.ReadString('\n')
					answers[i] = strings.TrimRight(line, "\r\n")
				} else {
					b, _ := term.ReadPassword(int(os.Stdin.Fd()))
					fmt.Fprintln(os.Stderr)
					answers[i] = string(b)
				}
			}
			return answers, nil
		}))
		loaded = append(loaded, "password(interactive)")
	}

	log.Printf("启用的认证方式: %s", strings.Join(loaded, ", "))

	// host key 校验
	var hostKeyCb ssh.HostKeyCallback
	if insecure {
		hostKeyCb = ssh.InsecureIgnoreHostKey()
	} else {
		home, _ := os.UserHomeDir()
		kh := filepath.Join(home, ".ssh", "known_hosts")
		cb, err := knownhosts.New(kh)
		if err != nil {
			log.Printf("读取 %s 失败 (%v),临时忽略 host key 校验", kh, err)
			hostKeyCb = ssh.InsecureIgnoreHostKey()
		} else {
			hostKeyCb = cb
		}
	}

	return &ssh.ClientConfig{
		User:            userName,
		Auth:            auths,
		HostKeyCallback: hostKeyCb,
		Timeout:         15 * time.Second,
	}, nil
}

func keepAlive(c *ssh.Client) {
	t := time.NewTicker(30 * time.Second)
	defer t.Stop()
	for range t.C {
		_, _, err := c.SendRequest("keepalive@openssh.com", true, nil)
		if err != nil {
			return
		}
	}
}

// ---------- 协议分发 ----------
func handleConn(c net.Conn, ssh *ssh.Client) {
	defer c.Close()
	br := bufio.NewReader(c)
	first, err := br.Peek(1)
	if err != nil {
		return
	}
	switch {
	case first[0] == 0x05:
		handleSocks5(br, c, ssh)
	case first[0] == 0x04:
		// SOCKS4 暂不支持
		log.Printf("收到 SOCKS4 请求,暂未实现")
	default:
		// 视为 HTTP
		handleHTTP(br, c, ssh)
	}
}

// ---------- SOCKS5 ----------

func handleSocks5(br *bufio.Reader, c net.Conn, sshc *ssh.Client) {
	// 握手: VER(1) NMETHODS(1) METHODS(n)
	hdr := make([]byte, 2)
	if _, err := io.ReadFull(br, hdr); err != nil {
		return
	}
	nMethods := int(hdr[1])
	if _, err := io.ReadFull(br, make([]byte, nMethods)); err != nil {
		return
	}
	// 回应: 无需认证
	if _, err := c.Write([]byte{0x05, 0x00}); err != nil {
		return
	}

	// 请求: VER CMD RSV ATYP DST.ADDR DST.PORT
	head := make([]byte, 4)
	if _, err := io.ReadFull(br, head); err != nil {
		return
	}
	if head[1] != 0x01 { // 只支持 CONNECT
		c.Write([]byte{0x05, 0x07, 0x00, 0x01, 0, 0, 0, 0, 0, 0})
		return
	}

	var host string
	switch head[3] {
	case 0x01: // IPv4
		buf := make([]byte, 4)
		if _, err := io.ReadFull(br, buf); err != nil {
			return
		}
		host = net.IP(buf).String()
	case 0x03: // 域名
		l, err := br.ReadByte()
		if err != nil {
			return
		}
		buf := make([]byte, int(l))
		if _, err := io.ReadFull(br, buf); err != nil {
			return
		}
		host = string(buf)
	case 0x04: // IPv6
		buf := make([]byte, 16)
		if _, err := io.ReadFull(br, buf); err != nil {
			return
		}
		host = net.IP(buf).String()
	default:
		c.Write([]byte{0x05, 0x08, 0x00, 0x01, 0, 0, 0, 0, 0, 0})
		return
	}
	portBuf := make([]byte, 2)
	if _, err := io.ReadFull(br, portBuf); err != nil {
		return
	}
	port := int(portBuf[0])<<8 | int(portBuf[1])
	target := net.JoinHostPort(host, strconv.Itoa(port))

	remote, err := sshc.Dial("tcp", target)
	if err != nil {
		log.Printf("SOCKS5 -> %s 失败: %v", target, err)
		c.Write([]byte{0x05, 0x05, 0x00, 0x01, 0, 0, 0, 0, 0, 0})
		return
	}
	defer remote.Close()
	if _, err := c.Write([]byte{0x05, 0x00, 0x00, 0x01, 0, 0, 0, 0, 0, 0}); err != nil {
		return
	}
	log.Printf("SOCKS5 %s -> %s", c.RemoteAddr(), target)
	pipe(c, remote, br)
}

// ---------- HTTP / HTTPS ----------

func handleHTTP(br *bufio.Reader, c net.Conn, sshc *ssh.Client) {
	req, err := http.ReadRequest(br)
	if err != nil {
		return
	}
	if req.Method == http.MethodConnect {
		// HTTPS 隧道
		target := req.URL.Host
		if !strings.Contains(target, ":") {
			target += ":443"
		}
		remote, err := sshc.Dial("tcp", target)
		if err != nil {
			fmt.Fprintf(c, "HTTP/1.1 502 Bad Gateway\r\n\r\n")
			return
		}
		defer remote.Close()
		fmt.Fprintf(c, "HTTP/1.1 200 Connection Established\r\n\r\n")
		log.Printf("HTTP CONNECT %s -> %s", c.RemoteAddr(), target)
		pipe(c, remote, br)
		return
	}

	// 普通 HTTP 转发
	if req.URL.Host == "" {
		fmt.Fprintf(c, "HTTP/1.1 400 Bad Request\r\n\r\n")
		return
	}
	host := req.URL.Host
	if !strings.Contains(host, ":") {
		host += ":80"
	}
	remote, err := sshc.Dial("tcp", host)
	if err != nil {
		fmt.Fprintf(c, "HTTP/1.1 502 Bad Gateway\r\n\r\n")
		return
	}
	defer remote.Close()

	// 重写为 origin-form,并剥离逐跳头
	req.RequestURI = ""
	req.URL.Scheme = ""
	req.URL.Host = ""
	stripHopByHop(req.Header)

	log.Printf("HTTP %s %s -> %s", req.Method, c.RemoteAddr(), host)
	if err := req.Write(remote); err != nil {
		return
	}
	// 双向转发后续字节(包含响应)
	pipe(c, remote, nil)
}

var hopHeaders = []string{
	"Connection", "Proxy-Connection", "Keep-Alive",
	"Proxy-Authenticate", "Proxy-Authorization",
	"Te", "Trailer", "Transfer-Encoding", "Upgrade",
}

func stripHopByHop(h http.Header) {
	for _, k := range hopHeaders {
		h.Del(k)
	}
}

// ---------- 双向转发 ----------

// pipe 在 c <-> remote 间转发。br 是带缓冲的客户端读端(可能已读入字节),
// 需要把缓冲里残留的数据也一并送往 remote。
func pipe(c net.Conn, remote net.Conn, br *bufio.Reader) {
	done := make(chan struct{}, 2)
	go func() {
		if br != nil && br.Buffered() > 0 {
			buf, _ := br.Peek(br.Buffered())
			remote.Write(buf)
			br.Discard(br.Buffered())
		}
		var src io.Reader = c
		if br != nil {
			src = br
		}
		io.Copy(remote, src)
		if tc, ok := remote.(closeWriter); ok {
			tc.CloseWrite()
		}
		done <- struct{}{}
	}()
	go func() {
		io.Copy(c, remote)
		if tc, ok := c.(closeWriter); ok {
			tc.CloseWrite()
		}
		done <- struct{}{}
	}()
	<-done
	<-done
}

type closeWriter interface{ CloseWrite() error }
