#!/bin/sh

MODEL_NUM=`cat /etc/MODEL_NUM`

echo 2096576 > /proc/sys/net/core/rmem_default;
echo 4192576 > /proc/sys/net/core/rmem_max;
echo 4096576 > /proc/sys/net/core/wmem_default;
echo 8192576 > /proc/sys/net/core/wmem_max;
echo 4096576 > /proc/sys/net/core/optmem_max;
echo 100000  > /proc/sys/net/core/netdev_max_backlog
echo 65536 262114 524288 > /proc/sys/net/ipv4/tcp_wmem
echo 65536 262114 524288 > /proc/sys/net/ipv4/tcp_rmem
echo 16384 65536 524288 > /proc/sys/net/ipv4/tcp_mem
echo 60000 64000 > /proc/sys/net/ipv4/ip_local_port_range;

echo 8192 > /proc/sys/vm/min_free_kbytes
echo 200  > /proc/sys/vm/vfs_cache_pressure

mkdir -m 0755 /tmp/sysinfo; /sbin/fw_printenv > /tmp/sysinfo/env
mkdir -m 0755 /tmp/upgrade
mkdir -m 0755 /tmp/smart
mkdir -m 0755 /dev/images
mkdir -m 0755 /dev/mjpeg

/usr/lib/cmdServer &
/usr/lib/sysconfig
/usr/sbin/hdd-info.sh
/usr/sbin/hdd-mount.sh mount ext4

/bin/hostname root
/sbin/fw_printenv ethaddr > /tmp/ethaddr
ln -sf /proc/self/fd /dev/fd

echo "load hi libs"
cd /usr/drv; ./load_master_estn -i
#/usr/sbin/load_master_estn 0

echo "start sata_link"
/usr/sbin/sata &

echo "start network service"
/usr/sbin/network.sh
/usr/sbin/telnetd &

ifconfig eth0 192.168.0.210
sleep 1
mkdir -p /tmp/eastern
route add default gw 192.168.0.1
ping -c 1 192.168.0.100
mount -t nfs -o nolock -o tcp 192.168.0.100:/nfs /tmp/eastern

HDD_NUM=`cat /tmp/num_of_hdd`

if [ $HDD_NUM == 0 ]; then
	echo "No Disk"
else
	if [ ! -e /storage/estn0/1/normal ]; then
		mkdir /storage/estn0/1/normal;
		echo "mkdir /storage/estn0/1/normal"
	fi

	if [ ! -e /storage/estn0/2/event/db ]; then
		mkdir -p /storage/estn0/2/event/db;
		echo "mkdir -p /storage/estn0/2/event/db"
	fi
fi

/usr/lib/ipcd &

echo "application start..."
BOOTMODE=`cat /tmp/bootmode.txt | sed 's/bootmode=//g'`

cd /tmp/eastern/usr_hi3531d/usr/lib; ./mainwidget -qws -display :/dev/fb0 -style CDE &
