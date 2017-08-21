#!/bin/sh

DEV=$1
SIZE1=`/sbin/fdisk -l $DEV | grep Disk | awk 'NR==1 { printf "%d",(($5 / 1024 / 1024 * 8)/10) }'`
SIZE2=`/sbin/fdisk -l $DEV | grep Disk | awk 'NR==1 { printf "%d",(($5 / 1024 / 1024 * 2)/10) }'`
INPUT="/tmp/input"
echo "HDD Partition => $DEV : [${DEV}1=${SIZE1}M, ${DEV}2=${SIZE2}M]"

rm -f $INPUT
echo "d" >> $INPUT
echo "1" >> $INPUT
echo "d" >> $INPUT
echo "2" >> $INPUT
echo "d" >> $INPUT
echo "3" >> $INPUT
echo "d" >> $INPUT
echo "p" >> $INPUT
echo "w" >> $INPUT
echo "# cmd : fdisk $DEV < $INPUT"
fdisk $DEV < $INPUT

rm -f $INPUT
echo "n" >> $INPUT
echo "p" >> $INPUT
echo "1" >> $INPUT
echo "" >> $INPUT
echo "+${SIZE1}M" >> $INPUT
echo "n" >> $INPUT
echo "p" >> $INPUT
echo "2" >> $INPUT
echo "" >> $INPUT
echo "+${SIZE2}M" >> $INPUT
echo "p" >> $INPUT
echo "w" >> $INPUT
echo "# cmd : fdisk $DEV < $INPUT"
fdisk $DEV < $INPUT
