#!/bin/bash

CORE_NUM=`cat /proc/cpuinfo | grep -c processor`
CORE_NUM=`expr $CORE_NUM \* 2`

EA_QT_COMM=arm-hisiv100

cp -arf mainwidget.basic.pro mainwidget.pro

export QMAKESPEC=/usr/local/Trolltech/QtEmbedded-4.5.3-$EA_QT_COMM/mkspecs/qws/linux-arm-g++ &&
export PATH=$PATH:/usr/local/Trolltech/QtEmbedded-4.5.3-$EA_QT_COMM/bin &&
/usr/local/Trolltech/QtEmbedded-4.5.3-$EA_QT_COMM/bin/qmake "QT -= network" -o Makefile mainwidget.pro &&

make -j $CORE_NUM && arm-hisiv100nptl-linux-strip mainwidget && cp -arf mainwidget ../../lib
