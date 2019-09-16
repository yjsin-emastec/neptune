#!/bin/sh
[ -z "$1" ] && echo "Error: should be run by udhcpc" && exit 1

#RESOLV_CONF="/etc/resolv.conf"
RESOLV_CONF="/tmp/resolv.conf"
DAEMON="/sbin/udhcpc"
SCRIPT="/usr/sbin/dhcpc.sh"
PIDFILE="/tmp/dhcpc.pid"
IFNAME1=`cat /etc/ifname1.conf`

dhcp_renew_bound()
{
	[ -n "$broadcast" ] && BROADCAST="broadcast $broadcast"
	[ -n "$subnet" ] && NETMASK="netmask $subnet"

	/sbin/ifconfig $IFNAME1 $ip $BROADCAST $NETMASK

	if [ -n "$router" ]
	then
		for i in $router
		do
			echo "adding router $i"
			route add default gw $i dev $IFNAME1
			valid="$valid|$i"

		done

		echo "deleting old routes"
		$(route -n | awk '/^0.0.0.0\W{9}('$valid')\W/ {next} /^0.0.0.0/ {print "route del -net "$1" gw "$2";"}')
	fi

	if [ -n "$dns" ]
	then
		echo -n > $RESOLV_CONF.tmp
		${domain:+echo search $domain} >> $RESOLV_CONF.tmp

		for i in $dns
		do
			echo "adding dns $i"
			echo nameserver $i >> $RESOLV_CONF.tmp
		done

		mv $RESOLV_CONF.tmp $RESOLV_CONF
	fi
}

case "$1" in

	start)
		echo -n "[DHCP] start....."
		if [ -f $PIDFILE ]; then
			echo "[Already Running]"
		else
			echo "OK"
			$DAEMON -b -t 1 -p $PIDFILE -s $SCRIPT -i $IFNAME1
		fi
		;;

	stop)
		echo -n "[DHCP] stop....."
		if [ -f $PIDFILE ]; then
			echo "OK"
			kill -9 `cat $PIDFILE`
			rm -f $PIDFILE
		else
			echo "Not Running"
		fi
		;;

	restart)
		$SCRIPT stop
		$SCRIPT start
		;;

	deconfig)
#		ifconfig $IFNAME1 0.0.0.0
		echo "[DHCP] deconfig.....OK"
		;;

	renew|bound)
		dhcp_renew_bound
		echo "[DHCP] renew.....OK"
		;;

	leasefail)
		echo "[DHCP] lease fail..."
#		sleep 10
#		$SCRIPT restart
		;;

	nak)
		echo "[DHCP] nak..."
		$SCRIPT stop
		;;

	*)
		echo "Unknown argument $1"
		echo "Usage: $SCRIPT {start|stop|restart}"
		;;

esac

exit 0
