#!/bin/bash

# Run script, after inserting SD card

# Compile kernel
make clean
make RASPI_MODEL=0

# Unmount SD card if it was automatically mounted from OS
# Create directory in /media in order to mount SD card
# Mount /boot partition

# Copy kernel to SD card
sudo cp kernel7.img /media/thanos/boot/kernel.img

# Forced cache data to be written to disk
sudo sync

# Unmount SD card (file, boot partitions)
sudo umount /dev/mmcblk0p1
sudo umount /dev/mmcblk0p2

# Unmount USB for SD card
# sudo umount /dev/sdb1
# sudo umount /dev/sdb2

# Check if it is unmount
lsblk -p