#!/bin/sh

ddr0=`cat /proc/media-mem | awk '/anonymous/ {print NR}'`
ddr1=`cat /proc/media-mem | awk '/ddr1/ {print NR}'`
end=`cat /proc/media-mem | awk 'END {print NR}'`
#echo "$ddr0,$ddr1,$end"

# mapped information
cat /proc/media-mem | awk '/ZONE/ {print $6$5}' | sed 's/nBYTES//'

# total
cat /proc/media-mem | awk '{print $7}' | grep 'length=' | sed 's/length=//' | sed 's/KB,//' | awk 'BEGIN {total=0} {total+=$1} END {print "total: "total"KB"}'
# ddr0
cat /proc/media-mem | awk 'NR > '"${ddr0}"'' | awk '{print $7}' | grep 'length=' | sed 's/length=//' | sed 's/KB,//' | awk 'BEGIN {total=0} {total+=$1} END{print "ddr0: "total"KB"}' 
# ddr1
cat /proc/media-mem | awk 'NR > '"${ddr1}"' && NR < '"${ddr0}"'' | awk '{print $7}' | grep 'length=' | sed 's/length=//' | sed 's/KB,//' | awk 'BEGIN {total=0} {total+=$1} END{print "ddr1: "total"KB"}' 





