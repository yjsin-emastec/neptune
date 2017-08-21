#!/bin/sh

echo $1  > ver.txt

V=`cat ver.txt`
D=`date '+%Y%m%d'`

echo "#define FIRMWARE_VERSION \"${V}_${D}\"" > include/eaVersion.h

cat include/eaVersion.h
