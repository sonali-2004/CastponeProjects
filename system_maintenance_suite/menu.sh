#!/bin/bash

while true
do
    clear
    echo "=============================="
    echo "   SYSTEM MAINTENANCE SUITE   "
    echo "=============================="
    echo "1. Backup Files"
    echo "2. Update System"
    echo "3. Clean System"
    echo "4. Monitor Logs"
    echo "5. Exit"
    echo "------------------------------"
    read -p "Enter your choice (1-5): " choice

    case $choice in
        1) bash backup.sh ;;
        2) bash update.sh ;;
        3) bash cleanup.sh ;;
        4) bash log_monitor.sh ;;
        5) echo "Exiting..."; exit 0 ;;
        *) echo "Invalid choice! Try again."; sleep 1 ;;
    esac
done
