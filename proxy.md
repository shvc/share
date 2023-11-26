# docker proxy
```
# command line arg
docker build --build-arg http_proxy=http://10.239.4.80:913 --build-arg https_proxy=http://10.239.4.80:913 .

# Dockerfile
ENV http_proxy 10.239.4.80:913
```

# ssh as proxy
```
ssh -D 127.0.0.1:8888 root@remote.ip
```

# resolv hostname via proxy
```
socks5h:// means that the hostname is resolved by the SOCKS server.
socks5://  mean that the hostname is resolved locally. 
```
