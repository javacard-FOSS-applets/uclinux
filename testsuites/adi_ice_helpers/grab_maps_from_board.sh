#!/bin/sh

ip=$1
if [ -z "$ip" ] ; then
	echo "Usage: $0 <IP of board>"
	exit 1
fi

rsh="rsh -l root $ip"
rcp="rcp root@$ip:"

$rsh cat /proc/kallsyms | grep " [Tt] " > System.map
$rsh cat /proc/maps | grep "x[ps] " | awk 'NF > 5' > user.list
$rsh cat /proc/sram | grep -v NULL > l1_sram.list
${rsh} lsmod | awk '{print $1}' | grep -v Module > modules.list
${rsh} ps | grep -v "\[.*\]" | grep -v PID | awk '{print $1 " " $5 }' | awk -F "[/ ]" '{print $NF" " $1}'> pid.list
