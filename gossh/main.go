package main

import (
	"bufio"
	"errors"
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
	"syscall"
	"time"

	"golang.org/x/crypto/ssh"
	"golang.org/x/crypto/ssh/agent"
	"golang.org/x/crypto/ssh/knownhosts"
	"golang.org/x/term"
)

func main() {
	listenAddr := flag.String("l", "0.0.0.0:8888", "local proxy listen address (SOCKS5 & HTTP)")
	identity := flag.String("i", "", "private key file path (comma-separated for multiple)")
	password := flag.String("p", "", "login password (optional; interactive prompt if omitted)")
	insecure := flag.Bool("insecure", false, "skip known_hosts verification")
	flag.Usage = func() {
		fmt.Fprintln(os.Stderr, "Usage: gossh [-l listen] [-i key] [-p password] [-insecure] user@host[:port]")
		flag.PrintDefaults()
	}
	flag.Parse()

	if flag.NArg() != 1 {
		flag.Usage()
		os.Exit(2)
	}
	userName, host, port, err := parseTarget(flag.Arg(0))
	if err != nil {
		log.Fatalf("parse target address failed: %v", err)
	}

	cfg, err := buildSSHConfig(userName, host, *identity, *password, *insecure)
	if err != nil {
		log.Fatalf("build SSH config failed: %v", err)
	}

	sshAddr := net.JoinHostPort(host, strconv.Itoa(port))
	log.Printf("connecting SSH: %s@%s ...", userName, sshAddr)
	client, err := ssh.Dial("tcp", sshAddr, cfg)
	if err != nil {
		log.Fatalf("SSH connection failed: %v", err)
	}
	defer client.Close()
	log.Printf("SSH connection established")

	go keepAlive(client)

	ln, err := net.Listen("tcp", *listenAddr)
	if err != nil {
		log.Fatalf("listen %s failed: %v", *listenAddr, err)
	}
	defer ln.Close()
	log.Printf("proxy listening: %s (SOCKS5 / HTTP)", *listenAddr)

	for {
		c, err := ln.Accept()
		if err != nil {
			log.Printf("accept failed: %v", err)
			continue
		}
		go handleConn(c, client)
	}
}

// ---------- Target address parsing ----------

// parseTarget parses "[user@]host[:port]", default port is 22.
// Supports IPv6 literals, e.g. user@[::1]:22.
func parseTarget(s string) (userName, host string, port int, err error) {
	port = 22
	if i := strings.IndexByte(s, '@'); i >= 0 {
		userName, s = s[:i], s[i+1:]
	} else {
		userName = currentUserName()
	}
	if userName == "" {
		return "", "", 0, fmt.Errorf("cannot determine username, use user@host format")
	}
	// try host:port (including IPv6 [::1]:port); treat as bare host on failure
	if h, p, e := net.SplitHostPort(s); e == nil {
		host = h
		if port, err = strconv.Atoi(p); err != nil {
			return "", "", 0, fmt.Errorf("invalid port %q: %w", p, err)
		}
	} else {
		host = strings.Trim(s, "[]")
	}
	if host == "" {
		return "", "", 0, fmt.Errorf("missing host")
	}
	return userName, host, port, nil
}

func currentUserName() string {
	if u, err := user.Current(); err == nil {
		return u.Username
	}
	return os.Getenv("USER")
}

// ---------- SSH configuration ----------

func buildSSHConfig(userName, host, identity, password string, insecure bool) (*ssh.ClientConfig, error) {
	var auths []ssh.AuthMethod
	var loaded []string

	// 1) ssh-agent (public key)
	if sock := os.Getenv("SSH_AUTH_SOCK"); sock != "" {
		if conn, err := net.Dial("unix", sock); err == nil {
			auths = append(auths, ssh.PublicKeysCallback(agent.NewClient(conn).Signers))
			loaded = append(loaded, "ssh-agent")
		}
	}

	// 2) private key files (public key)
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
				fmt.Fprintf(os.Stderr, "key %s is encrypted, enter passphrase: ", kf)
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

	// 3) password — coexists with private key, server falls back after rejecting public key
	if password != "" {
		auths = append(auths, ssh.Password(password))
		loaded = append(loaded, "password(cli)")
	} else {
		// interactive: only prompt when server actually requests password
		auths = append(auths, ssh.PasswordCallback(func() (string, error) {
			fmt.Fprintf(os.Stderr, "password for %s@%s: ", userName, host)
			pp, err := term.ReadPassword(int(os.Stdin.Fd()))
			fmt.Fprintln(os.Stderr)
			return string(pp), err
		}))
		// also support keyboard-interactive (some servers only enable this)
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

	log.Printf("auth methods: %s", strings.Join(loaded, ", "))

	// host key verification
	var hostKeyCb ssh.HostKeyCallback
	if insecure {
		hostKeyCb = ssh.InsecureIgnoreHostKey()
	} else {
		home, _ := os.UserHomeDir()
		kh := filepath.Join(home, ".ssh", "known_hosts")
		cb, err := knownhosts.New(kh)
		if err != nil {
			log.Printf("read %s failed (%v), temporarily skipping host key check", kh, err)
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
			log.Fatalf("SSH keepalive failed, connection lost: %v", err)
		}
	}
}

// ---------- Protocol dispatch ----------
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
		// SOCKS4 not supported
		log.Printf("received SOCKS4 request, not implemented")
	default:
		// treat as HTTP
		handleHTTP(br, c, ssh)
	}
}

// isSSHTransportDead checks if the SSH transport is unrecoverable
func isSSHTransportDead(err error) bool {
	return errors.Is(err, syscall.ENETDOWN) ||
		errors.Is(err, syscall.ECONNRESET) ||
		errors.Is(err, syscall.EPIPE) ||
		errors.Is(err, syscall.ENETRESET) ||
		errors.Is(err, syscall.ECONNABORTED) ||
		errors.Is(err, syscall.EHOSTDOWN) ||
		errors.Is(err, syscall.EHOSTUNREACH) ||
		errors.Is(err, net.ErrClosed)
}

// ---------- SOCKS5 ----------

func handleSocks5(br *bufio.Reader, c net.Conn, sshc *ssh.Client) {
	// handshake: VER(1) NMETHODS(1) METHODS(n)
	hdr := make([]byte, 2)
	if _, err := io.ReadFull(br, hdr); err != nil {
		return
	}
	nMethods := int(hdr[1])
	if _, err := io.ReadFull(br, make([]byte, nMethods)); err != nil {
		return
	}
	// reply: no auth required
	if _, err := c.Write([]byte{0x05, 0x00}); err != nil {
		return
	}

	// request: VER CMD RSV ATYP DST.ADDR DST.PORT
	head := make([]byte, 4)
	if _, err := io.ReadFull(br, head); err != nil {
		return
	}
	if head[1] != 0x01 { // only CONNECT supported
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
	case 0x03: // domain name
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
		log.Printf("SOCKS5 -> %s failed: %v", target, err)
		c.Write([]byte{0x05, 0x05, 0x00, 0x01, 0, 0, 0, 0, 0, 0})
		if isSSHTransportDead(err) {
			log.Fatalf("SSH transport dead, exiting: %v", err)
		}
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
		// HTTPS tunnel
		target := req.URL.Host
		if !strings.Contains(target, ":") {
			target += ":443"
		}
		remote, err := sshc.Dial("tcp", target)
		if err != nil {
			fmt.Fprintf(c, "HTTP/1.1 502 Bad Gateway\r\n\r\n")
			if isSSHTransportDead(err) {
				log.Fatalf("SSH transport dead, exiting: %v", err)
			}
			return
		}
		defer remote.Close()
		fmt.Fprintf(c, "HTTP/1.1 200 Connection Established\r\n\r\n")
		log.Printf("HTTP CONNECT %s -> %s", c.RemoteAddr(), target)
		pipe(c, remote, br)
		return
	}

	// plain HTTP forward
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
		if isSSHTransportDead(err) {
			log.Fatalf("SSH transport dead, exiting: %v", err)
		}
		return
	}
	defer remote.Close()

	// rewrite to origin-form, strip hop-by-hop headers
	req.RequestURI = ""
	req.URL.Scheme = ""
	req.URL.Host = ""
	stripHopByHop(req.Header)

	log.Printf("HTTP %s %s -> %s", req.Method, c.RemoteAddr(), host)
	if err := req.Write(remote); err != nil {
		return
	}
	// bidirectional forward (including response)
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

// ---------- Bidirectional forward ----------

// pipe forwards between c <-> remote. br is the buffered client reader
// (may have buffered bytes), any leftover data must also be sent to remote.
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
