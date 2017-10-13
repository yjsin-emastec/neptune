#!/bin/sh

err_exit()
{
    echo "FAIL"
    echo "---------------------"
    echo " Image Header Error !"
    echo "---------------------"
    echo ""
    rm -f *.tmp
    exit 1
}

if [ ! -d tmp ]; then
    echo "tmp directory not found!"
    exit 1
fi

case "$1" in
    *)
        mkimage_files/eaimage tmp/host/images/bootld.img $1 0 bootld.tmp
        [ $? != 0 ] && err_exit

        mkimage_files/eaimage tmp/host/images/kernel.img $1 3 kernel.tmp
        [ $? != 0 ] && err_exit

        mkimage_files/eaimage tmp/host/images/btlogo.img $1 4 btlogo.tmp
        [ $? != 0 ] && err_exit

        mkimage_files/eaimage tmp/host/images/rootfs.img $1 5 rootfs.tmp
        [ $? != 0 ] && err_exit
        ;;
esac

cat bootld.tmp kernel.tmp btlogo.tmp rootfs.tmp > cardvr.bin
rm -f *.tmp
cp -a cardvr.bin /tftpboot
echo OK
echo ""
exit 0
