#!/bin/bash

PROJECT_ROOT=../../
CORE_NUM=`cat /proc/cpuinfo | grep -c processor`
CORE_NUM=`expr $CORE_NUM \* 2`

cp -arf mainwidget.eastern.pro mainwidget.pro
export QMAKESPEC=/usr/local/Trolltech/QtEmbedded-arm-hisiv600/mkspecs/qws/linux-arm-g++ &&
export PATH=$PATH:/usr/local/Trolltech/QtEmbedded-arm-hisiv600/bin &&
/usr/local/Trolltech/QtEmbedded-arm-hisiv600/bin/qmake "QT -= network" -o Makefile mainwidget.pro &&
make -j $CORE_NUM && arm-hisiv600-linux-strip mainwidget && cp -arf mainwidget ${PROJECT_ROOT}lib
