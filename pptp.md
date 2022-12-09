## Server


## Client
```
# setup pptp client
pptpsetup --create hkvpn --server server-ip-addr --username hkvpn --password you-password --encrypt --start

# direct tunnelled packets to the tunnel server
route add -host server-ip-addr dev eth0

# direct all other packets into the tunnel
route del default eth0
route add default dev ppp0
```
