https://phoenixnap.com/kb/ssh-port-forwarding  
https://www.cnblogs.com/cangqinglang/p/12732661.html  


### 0. ssh server config
- config sshd `/etc/ssh/sshd_config`
```
AllowAgentForwarding yes
AllowTcpForwarding yes
GatewayPorts yes
X11Forwarding yes
X11DisplayOffset 10
X11UseLocalhost no
```
- restart sshd  
`systemctl restart sshd`

### 1. ClientA Config
- copy ssh-key to server  
`ssh-copy-id root@serverip`

- autossh configuration  
```sh
yum install autossh

cat > /etc/default/autossh <<EOF
AUTOSSH_POLL=60
AUTOSSH_FIRST_POLL=30
AUTOSSH_GATETIME=0
AUTOSSH_PORT=23456
EOF

cat > /etc/systemd/system/autossh.service <<EOF
[Unit]
Description=autossh
Wants=network-online.target
After=network-online.target

[Service]
Type=simple
#User=autossh
EnvironmentFile=/etc/default/autossh
ExecStart=/usr/bin/autossh -i /root/.ssh/id_rsa -CqNR 0.0.0.0:20022:localhost:22 root@serverip
Restart=always
RestartSec=60

[Install]
WantedBy=multi-user.target
EOF

systemctl start autossh
systemctl enable autossh
```

### 2. ClientB Access ClientA
- Install sshpass  
```sh
ssh -p 20022 root@serverip

# or use sshpass
sshpass -p clientpass ssh -p 20022 root@serverip
```

