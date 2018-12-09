#!/bin/bash

cd /home/pi/piotbox

prm=$1

pidof piotbox >/dev/null
if [[ $? -ne 1 ]] ; then 
   exit
fi

# sudo ./piotbox $prm
sudo ./piotbox examples/test.lua

ret=$?
if [[ $ret == 91 ]]; then
   echo "SHUTDOWN, CODE=$ret"
   sudo shutdown -h now
elif [[ $ret == 92 ]]; then
   echo "REBOOT, CODE=$ret"
   sudo reboot
elif [[ $ret == 93 ]]; then
   echo "RESTART, CODE=$ret"
   sudo ./piotbox $prm
elif [[ $ret == 1 ]]; then
   echo "ERROR, CODE=$ret"
   sudo sudo shutdown -h now   
else
   echo "STOPPED, CODE=$ret"
   cd ~
fi
