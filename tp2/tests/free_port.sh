#!/bin/sh

i=$1;
while [ $i -le 1000000 ]; do 
    netstat -a|grep tcp|grep "LISTEN\|TIME_WAIT" | awk '{print $4;}'|awk 'BEGIN { FS = ":" } ; { print $2 }'|grep -q $i
  if [ $? -ne "0" ]; then
    break
  fi
  i=$(($i+1));
done

echo "$i"
