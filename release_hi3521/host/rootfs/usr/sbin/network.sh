#!/bin/sh

IFNAME1=`cat /etc/ifname1.conf`

# local interface
ifconfig lo 127.0.0.1

# set MAC address
MAC_ADDR=`cat /tmp/ethaddr | sed 's/ethaddr=//g'`
ifconfig $IFNAME1 hw ether $MAC_ADDR

ifconfig $IFNAME1 up
