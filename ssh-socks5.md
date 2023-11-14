# start a local socks5 prox server
ssh -o ServerAliveInterval=180 -o ServerAliveCountMax=2 -D 0.0.0.0:8888 user@remote-ip
