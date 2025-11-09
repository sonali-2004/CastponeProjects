#!/bin/bash

clear
echo "=============================="
echo "         BACKUP TOOL         "
echo "=============================="

# Ask user for source folder
read -p "Enter the folder you want to backup: " source

# Check if folder exists
if [ ! -d "$source" ]; then
    echo "Error: Source folder does not exist!"
    sleep 2
    exit 1
fi

# Ask for destination folder
read -p "Enter the destination folder: " destination

# Create destination if it doesn't exist
if [ ! -d "$destination" ]; then
    echo "Destination folder does not exist. Creating it..."
    mkdir -p "$destination"
fi

# Create timestamp
timestamp=$(date +"%Y-%m-%d_%H-%M-%S")

# Create backup folder name
backup_folder="$destination/backup_$timestamp"

echo "Creating backup folder: $backup_folder"
mkdir -p "$backup_folder"

echo "Backing up files..."
cp -r "$source"/* "$backup_folder"

echo "✅ Backup completed successfully!"
echo "Backup stored at: $backup_folder"

sleep 2
