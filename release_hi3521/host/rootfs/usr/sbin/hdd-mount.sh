#!/bin/sh

case "$1" in

	mount)
		mount -t ext4 /dev/sda1 /storage/estn0/1 2> /dev/null
		mount -t ext4 /dev/sdb1 /storage/estn1/1 2> /dev/null
		mount -t ext4 /dev/sdc1 /storage/estn2/1 2> /dev/null
		mount -t ext4 /dev/sdd1 /storage/estn3/1 2> /dev/null
		mount -t ext4 /dev/sde1 /storage/estn4/1 2> /dev/null
		mount -t ext4 /dev/sdf1 /storage/estn5/1 2> /dev/null
		mount -t ext4 /dev/sdg1 /storage/estn6/1 2> /dev/null
		mount -t ext4 /dev/sdh1 /storage/estn7/1 2> /dev/null
		mount -t ext4 /dev/sda2 /storage/estn0/2  2> /dev/null
		mount -t ext4 /dev/sdb2 /storage/estn1/2  2> /dev/null
		mount -t ext4 /dev/sdc2 /storage/estn2/2  2> /dev/null
		mount -t ext4 /dev/sdd2 /storage/estn3/2  2> /dev/null
		mount -t ext4 /dev/sde2 /storage/estn4/2  2> /dev/null
		mount -t ext4 /dev/sdf2 /storage/estn5/2  2> /dev/null
		mount -t ext4 /dev/sdg2 /storage/estn6/2  2> /dev/null
		mount -t ext4 /dev/sdh2 /storage/estn7/2  2> /dev/null

		if [ $2 == xfs ]; then
			mount -t xfs /dev/sda1 /storage/estn0/1 2> /dev/null
			mount -t xfs /dev/sdb1 /storage/estn1/1 2> /dev/null
			mount -t xfs /dev/sdc1 /storage/estn2/1 2> /dev/null
			mount -t xfs /dev/sdd1 /storage/estn3/1 2> /dev/null
			mount -t xfs /dev/sde1 /storage/estn4/1 2> /dev/null
			mount -t xfs /dev/sdf1 /storage/estn5/1 2> /dev/null
			mount -t xfs /dev/sdg1 /storage/estn6/1 2> /dev/null
			mount -t xfs /dev/sdh1 /storage/estn7/1 2> /dev/null
			mount -t xfs /dev/sda2 /storage/estn0/2  2> /dev/null
			mount -t xfs /dev/sdb2 /storage/estn1/2  2> /dev/null
			mount -t xfs /dev/sdc2 /storage/estn2/2  2> /dev/null
			mount -t xfs /dev/sdd2 /storage/estn3/2  2> /dev/null
			mount -t xfs /dev/sde2 /storage/estn4/2  2> /dev/null
			mount -t xfs /dev/sdf2 /storage/estn5/2  2> /dev/null
			mount -t xfs /dev/sdg2 /storage/estn6/2  2> /dev/null
			mount -t xfs /dev/sdh2 /storage/estn7/2  2> /dev/null
		fi
		;;

	umount)
		umount /storage/estn0/1 2> /dev/null
		umount /storage/estn1/1 2> /dev/null
		umount /storage/estn2/1 2> /dev/null
		umount /storage/estn3/1 2> /dev/null
		umount /storage/estn4/1 2> /dev/null
		umount /storage/estn5/1 2> /dev/null
		umount /storage/estn6/1 2> /dev/null
		umount /storage/estn7/1 2> /dev/null
		umount /storage/estn0/2  2> /dev/null
		umount /storage/estn1/2  2> /dev/null
		umount /storage/estn2/2  2> /dev/null
		umount /storage/estn3/2  2> /dev/null
		umount /storage/estn4/2  2> /dev/null
		umount /storage/estn5/2  2> /dev/null
		umount /storage/estn6/2  2> /dev/null
		umount /storage/estn7/2  2> /dev/null
		;;

	*)
		echo "Usage: hdd-mount.sh {mount|umount}"
		;;

esac

exit 0

