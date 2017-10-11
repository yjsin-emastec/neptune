#!/bin/bash

echo "Copy shared library to \"$1\"" &&

cp libappmanager.so    $1 &&
cp libtestmgr.so       $1 &&
cp libcore.so          $1 &&
cp libdevmanager.so    $1 &&
cp libevent.so         $1 &&
cp librtc.so           $1 &&
cp libgsensor.so       $1 &&
cp libtemperature.so   $1 &&
cp libnmea.so          $1 &&
cp libdiskmgr.so       $1 &&
cp libgps.so           $1 &&
cp libkeypad.so        $1 &&
cp libver.so           $1 &&
cp libnetmanager.so    $1 &&
cp libwork.so          $1 &&
cp libdata.so          $1 &&
cp libpb.so            $1 &&
cp libutils.so         $1 &&
cp libnetipc.so        $1 &&
cp libsocket.so        $1 &&
cp libvenc.so          $1 &&
cp libmediabackup.so   $1 &&
cp libipc.so           $1 &&
cp libosal.so          $1 &&
cp cmdServer           $1 &&
cp libhimem.so         $1 &&

echo "Copy done."
