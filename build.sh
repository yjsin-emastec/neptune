#!/bin/sh

rm -f model_name.txt model_num.txt ver.txt *.bin

# generate rules.mk
sh script/genrule.sh $1 &&

# build all
make &&

# make image
make Reinstall &&

if [ -f model_num.txt ]
then
    N=`cat model_num.txt`       # model number
    M=`cat model_name.txt`      # model name
    v=`cat vendor.txt`          # vendor
    V=`cat ver.txt`             # version
    D=`date '+%Y%m%d'`          # date

    BIN="mdvr_${v}_${M}_${V}_${D}.bin"
    bin=`echo ${BIN} | tr A-Z a-z`

    echo ""
    echo "make ${bin} for \"${v}_${M}\""
    echo ""

    sh script/makeMobileDvr.sh ${N}

    cp mdvr.bin ${bin}
else
    echo "No such model_num.txt"
    exit 1
fi

exit 0
