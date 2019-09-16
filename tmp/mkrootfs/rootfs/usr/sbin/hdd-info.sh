#!/bin/sh
NUM=0
SLOT=
ATA_ID=0
SECTORS=
for i in a b c d e f g h
do
    if [ -b /dev/sd$i ]; then
        if [ `cat /sys/block/sd$i/removable` == 0 ]; then

            if [ `cat /tmp/smart/sd$i.cap` == 1 ]; then
                echo "SMART is available"
                /usr/sbin/smartctl -s on -a /dev/sd$i > /tmp/smart/sd$i.tmp
                SECTORS=`/sbin/fdisk -lu /dev/sd$i | grep total | awk '{ print $8 }'`
            else
                echo "SMART is NOT available"
            fi

            SLOT=`cat /tmp/smart/smart$NUM.info | grep SLOT`
            ATA_ID=`cat /sys/block/sd$i/queue/rotational`
            echo $SLOT > /tmp/smart/smart$NUM.info
            cat /tmp/smart/sd$i.tmp | grep 'Device Model'  >> /tmp/smart/smart$NUM.info
            cat /tmp/smart/sd$i.tmp | grep 'User Capacity' >> /tmp/smart/smart$NUM.info
            cat /tmp/smart/sd$i.tmp | grep 'Power_On_Hours'         | awk '{ print $2,$10 }' >>  /tmp/smart/smart$NUM.info
            cat /tmp/smart/sd$i.tmp | grep 'Temperature_Cel'        | awk '{ print $2,$10 }' >>  /tmp/smart/smart$NUM.info
            cat /tmp/smart/sd$i.tmp | grep 'Reallocated_Sector_Ct'  | awk '{ print $2,$10 }' >>  /tmp/smart/smart$NUM.info
            cat /tmp/smart/sd$i.tmp | grep 'Spin_Retry_Count'       | awk '{ print $2,$10 }' >>  /tmp/smart/smart$NUM.info
            cat /tmp/smart/sd$i.tmp | grep 'Current_Pending_Sector' | awk '{ print $2,$10 }' >>  /tmp/smart/smart$NUM.info
            cat /tmp/smart/sd$i.tmp | grep 'Offline_Uncorrectable'  | awk '{ print $2,$10 }' >>  /tmp/smart/smart$NUM.info
            echo "ATA_ID $ATA_ID" >> /tmp/smart/smart$NUM.info
            echo "Total_Sectors $SECTORS"  >> /tmp/smart/smart$NUM.info
            NUM=$(($NUM + 1))
        fi
    fi
done
exit 0
