#!/bin/bash

clear
echo "=============================="
echo "         CLEANUP TOOL         "
echo "=============================="

echo "Cleaning temporary files..."
rm -rf /tmp/*

echo "Cleaning apt cache..."
sudo apt clean

echo "Cleaning thumbnails..."
rm -rf ~/.cache/thumbnails/*

echo "✅ Cleanup completed!"
sleep 2
