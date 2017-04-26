## 命令设置ip地址

1. 设置IP sudo ifconfig eth0 203.171.239.155 netmask 255.255.255.224 这样就算设置好了网卡eth0的IP地址和子网掩码
2. 设置网关 sudo route add default gw 203.171.239.129
3. 设置DNS 修改/etc/resolv.conf，在其中加入 nameserver DNS的地址1 nameserver DNS的地址2 完成。不过，这样设置之后，下次开机时候似乎IP又不存在了。

## 直接修改系统配置文件

Ubuntu的网络配置文件是：/etc/network/interfaces
修改完生效的命令：sudo /etc/init.d/networking restart

### DHCP 方式配置网卡

编辑 /etc/network/interfaces 以下边的两行替换eth0相关的行

```
    # The primary network interface - use DHCP to find our address  
    auto eth0  
    iface eth0 inet dhcp 
```
使用命令 sudo /etc/init.d/networking restart 生效

> 也可以直接使用：sudo dhclient eth0 

### 为网卡配置静态IP地址

配置如下：
```
    auto eth0  
    iface eth0 inet static  
    address 192.168.3.90  
    gateway 192.168.3.1  
    netmask 255.255.255.0  
    #network 192.168.3.0  
    #broadcast 192.168.3.255 
    # 配置dns 多个使用空格分开
    dnd_ nameservers 114.114.114.114

auto eth0
iface eth0 inet static
address 10.1.22.21
gateway 10.1.22.254
netmask 255.255.255.0
dns-nameservers 219.141.136.10 219.141.140.10

```

别忘记生效
