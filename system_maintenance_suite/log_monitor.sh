#!/bin/bash

clear
echo "=============================="
echo "       LOG MONITOR TOOL       "
echo "=============================="
echo "Press CTRL + C to stop"
echo "------------------------------"

# Live monitoring of system logs
sudo tail -f /var/log/syslog
