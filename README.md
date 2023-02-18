## npm/pnpm config
```
pnpm config set registry https://registry.npmmirror.com/
```

## Centos remove unused packages
```
yum remove empathy cheese gnome-dictionary gnome-contacts\
    gnome-weather totem orca system-config-printer gnome-tweak-tool\
    pulseaudio-utils alsa-plugins-pulseaudio gnome-video-effects\
    alsa-firmware alsa-utils\
    system-config-printer-udev system-config-printer-libs gutenprint firewalld 
```

## tcpdump http headers
```
tcpdump -n -S -s 0 -A 'tcp dst port 80' | grep -B3 -A10 "Server"
tcpdump -n -S -s 0 -A 'tcp and host 172.16.3.24 and port 9020'
```

## virsh console Centos7
OS installation  
```
virt-install –name centos7 –ram 1024 –disk path=/centos7.qcow2\
  –location /CentOS-7-x86_64-DVD-1708.iso –nographics\
  –accelerate –extra-args=”console=ttyS0″ –network bridge=virbr0
```
OS setting
```
systemctl enable serial-getty@ttyS0.service
systemctl start serial-getty@ttyS0.service
```

## docker install offline
https://stackoverflow.com/questions/53680374/how-to-install-docker-ce-without-internet-and-intranet-yum-repository

## github
```
LGTM: Looks Good To Me.
SGTM: Sounds Good To Me.
WIP: Work In Progress. 
PTAL: Please Take A Look.
TBR: To Be Reviewed. 
TL;DR: Too Long; Didn't Read. 
TBD: To Be Done(or Defined/Discussed/Decided/Determined). 
```
