
## perf
#### 1. IO perf(hdparm read/ dd write)
| raspberry pi 3b+ | hdparm(r) cache | hdparm(r) buffer | dd (w dsync) |    dd(w)  |
| :--------------- | :--------------:| :---------------:|:------------:|:---------:|
| **TF card**      |    772.65 MB/s  |    21.78 MB/s    |  14.0 MB/s   | 18.9 MB/s |
| **hard disk**    |    806.99 MB/s  |    33.28 MB/s    |  9.6 MB/s    | 33.3 MB/s |

#### 2. Network perf
| raspberry pi 3b+ | scp(upload 2GB) | http(upload 3GB) | scp(download) | http(download)|
| :--------------- | :--------------:| :---------------:|:------------:|:---------:|
| **2.4G**         |     2.2 MB/s    |    2.27  MB/s    |     MB/s     |    MB/s   |
| **5G**           |     2.5 MB/s    |          MB/s    |     MB/s     |    MB/s   |

### hostapd config
#### 0. Install hostapd
`apt install hostapd`
#### 1. Configuration 2.4G #5G
Edit `/etc/hostapd/config`
```
interface=wlan0
driver=nl80211
hw_mode=g  #a
macaddr_acl=0
channel=6  #36
ssid=raspberry
wpa=2
wpa_key_mgmt=WPA-PSK
wpa_passphrase=password
rsn_pairwise=CCMP
```

### raspbian config
#### 0. Remove boot raspberry logo
Add `logo.nologo` to `/boot/cmdline.txt`
#### 1. Rename default username
```
usermod -l mshare -d /home/mshare -m pi
groupmod -n mshare pi
```
#### 1. lightdm config
Just edit `/etc/lightdm/pi-greeter.conf` to remove raspberry logo  
#### 2. apt update got hash mismatch
Edit `/etc/apt.d/source.list`
```
sudo apt-get clean
sudo rm /var/lib/apt/lists/partial/*
sudo nano /etc/apt/sources.list

deb http://archive.raspbian.org/raspbian wheezy main contrib non-free
deb-src http://archive.raspbian.org/raspbian wheezy main contrib non-free

wget http://archive.raspbian.org/raspbian.public.key -O - | sudo apt-key add -

sudo apt-get update
```

## Install 64bit Centos
  1. Download Image  
  https://people.centos.org/pgreco/  
  https://mirrors.huaweicloud.com/centos-altarch/  
  http://isoredirect.centos.org/altarch/7/isos/aarch64/  
  
  2. Write Image to sd-card
  3. boot(root/centos)
  4. Resize/Expand rootfs
  ```
  /usr/bin/rootfs-expand #由于还没有这个命令，需要通过fdisk 实现新分区
  fdisk /dev/mmcblk0
  新建分区n /dev/mmcblk0p4
  删除分区d /dev/mmcblk0p3
  新建分区n /dev/mmcblk0p3
  删除分区d /dev/mmcblk0p4
  w
  q
  reboot
  resize2fs /dev/mmcblk0p3
  ```
