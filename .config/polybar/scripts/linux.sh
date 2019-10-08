#!/bin/bash
n=$1
while [[ 0 != $n ]]
do
  res=$(xprop -id $(xprop -root 32x '\t$0' _NET_ACTIVE_WINDOW | cut -f 2) WM_CLASS WM_NAME)
   if [ "$n" -gt "0" ]
   then
   		n=`expr $n - 1`
   fi
done
class=$(echo $res | cut -d '"' -f2)
name=$(echo $res | cut -d '"' -f6)

echo $class ":" $name
