- install centos5
```
virt-install \
 --name centos5.9 \
 --ram 1024 \
 --disk size=50 \
 --vcpus 2 \
 --os-type linux \
 --os-variant rhel5.9 \
 --network bridge=virbr0 \
 --graphics none \
 --console pty,target_type=serial \
 --location /home/CentOS-5.9-x86_64-bin-DVD-1of2.iso \
 --extra-args 'console=ttyS0,115200n8 serial'


virt-install \
 --name centos5.9 \
 --ram 1024 \
 --disk size=50 \
 --vcpus 2 \
 --os-type linux \
 --os-variant rhel5.9 \
 --network type=direct,source=em2,source_mode=bridge,model=virtio \
 --graphics none \
 --console pty,target_type=serial \
 --location /home/CentOS-5.9-x86_64-bin-DVD-1of2.iso \
 --extra-args 'console=ttyS0,115200n8 serial'
 ```
 
 - install centos7
 ```
virt-install \
--name ctos7 \
--ram 1024 \
--disk path=/mnt/sdd/ctos7.qcow2 \
--vcpus 1 \
--os-type linux \
--os-variant rhel7.0 \
--network bridge=virbr0 \
--graphics none \
--console pty,target_type=serial \
--location  /mnt/sdb/CentOS-7-x86_64-Minimal-2003.iso \
--extra-args 'console=ttyS0,115200n8 serial'
 ```
 
 - install centos8
 ```
 #--network bridge=virbr0
virt-install \
--name centos8 \
--ram 4096 \
--disk path=/mnt/sdc/centos8.qcow2 \
--vcpus 2 \
--os-type linux \
--os-variant rhel8.0 \
--network type=direct,source=em1,source_mode=bridge,model=virtio \
--graphics none \
--console pty,target_type=serial \
--location /mnt/sdc/CentOS-8.1.1911-x86_64-dvd1.iso \
--extra-args 'console=ttyS0,115200n8 serial'
 ```
 
 - install deb
 ```
 virt-install \
--name debian10 \
--ram 1024 \
--disk path=/mnt/sdd/debian10.qcow2 \
--vcpus 1 \
--os-type linux \
--os-variant debian10 \
--network type=direct,source=em1,source_mode=bridge,model=virtio \
--graphics none \
--console pty,target_type=serial \
--location /root/debian-10.12.0-amd64-netinst.iso \
--extra-args 'console=ttyS0,115200n8 serial'
 ```
 
- snapshot
```
# create
virsh snapshot-create-as --domain ecs99 --name ecs99_snap01 --description 'new install @2020-02-03'
# list
virsh snapshot-list ecs99_snap01
virsh snapshot-info --domain ecs99 --snapshotname ecs99_snap01
# revert
virsh snapshot-revert ecs99 ecs99_snap01
```

https://raymii.org/s/articles/virt-install_introduction_and_copy_paste_distro_install_commands.html
