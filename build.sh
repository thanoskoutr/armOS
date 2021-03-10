#!/bin/bash

# Get Raspi model number from 1st argument - Default: Model 0
MODEL=${1:-0}
MOUNT_DIR="/media/thanos"

# Run script, after inserting SD card

# Compile kernel
make clean
make RASPI_MODEL=${MODEL}

# Compile armstub
if [ $MODEL == 4 ]; then
	make RASPI_MODEL=${MODEL} armstub
fi

# Unmount SD card if it was automatically mounted from OS
# Create directory in /media in order to mount SD card
# Mount /boot partition

# Remove any previous kernel images on the /boot partition
rm -f ${MOUNT_DIR}/boot/kernel*.img
# Remove any previous armstub on the /boot partition
rm -f ${MOUNT_DIR}/boot/armstub*.bin

# Copy kernel to SD card
if [ $MODEL == 0 ]; then
	rm -f ${MOUNT_DIR}/boot/config.txt
	cp config0.txt ${MOUNT_DIR}/boot/config.txt
	cp kernel7.img ${MOUNT_DIR}/boot/kernel.img
elif [ $MODEL == 4 ]; then
	cp armstub-new.bin ${MOUNT_DIR}/boot/armstub-new.bin
	cp config4.txt ${MOUNT_DIR}/boot/config.txt
	cp kernel8.img ${MOUNT_DIR}/boot/kernel8.img
fi

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
