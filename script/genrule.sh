#!/bin/sh

RULESMK=rules.mk
PID=""
if [ "$1" = "pwd" ]; then
    PID=`basename $PWD`
else
    if [ "$1" != "" ]; then
        cat script/mdb.txt | grep $1
    else
        cat script/mdb.txt
    fi

    echo "Select PID, type and then press ENTER..."
    read PID
fi

exec < script/mdb.txt

while read A1 A2 A3 A4 A5 A6 A7 A8 A9 A10
do
    if [ ${A1} = ${PID} ]; then
        echo "YOUR SELECTION IS ${A1}-${A2}-${A3}-${A4}-${A5}-${A6}-${A7}-${A8}-${A9}-${A10}"
        echo "EA_ID             = ${A1}" >> $RULESMK
        echo "EA_VENDOR         = ${A2}" >> $RULESMK
        echo "EA_MODEL          = ${A3}" >> $RULESMK
        echo "EA_SUB_MODEL      = ${A4}" >> $RULESMK
        echo "EA_OEM            = ${A5}" >> $RULESMK
        echo "EA_SUB_OEM        = ${A6}" >> $RULESMK
        echo "EA_REGION         = ${A7}" >> $RULESMK
        echo "EA_MODEL_NAME     = ${A8}" >> $RULESMK
        echo "GUI_TYPE          = ${A9}" >> $RULESMK
        echo ""
        cat script/skel.mk >> $RULESMK
        echo "$RULESMK generated."
        echo "${A2}"  > vendor.txt
        echo "${A3}"  > model_num.txt
        echo "${A8}"  > model_name.txt
        echo "#define MODEL_NAME \"${A8}\"" > utils/inc/model_util.h

        case "${A3}" in
            1)
                echo "arm-hisiv100" > arch.txt
                ;;

            *)
                echo "arm-hisiv100" > arch.txt
                ;;
        esac

        exit 0
    fi


done < script/mdb.txt

echo "No such PID. ${PID}"

exit 1
