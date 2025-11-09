#!/bin/bash

clear
echo "=============================="
echo "        SYSTEM UPDATE         "
echo "=============================="

echo "Updating package list..."
sudo apt update

echo "Upgrading packages..."
sudo apt upgrade -y

echo "Removing unnecessary packages..."
sudo apt autoremove -y
sudo apt autoclean -y

echo "✅ System updated and cleaned successfully!"
sleep 2
