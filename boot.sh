#!/bin/sh

# Compile boot.S
arm-none-eabi-gcc -mcpu=cortex-a7 -fpic -ffreestanding -c boot.S -o boot.o
# Compile boot_zero.S
# arm-none-eabi-gcc -mcpu=arm1176jzf-s -fpic -ffreestanding -c boot_zero.S -o boot.o

# Compile kernel.c
arm-none-eabi-gcc -mcpu=cortex-a7 -fpic -ffreestanding -O2 -Wall -Wextra -c kernel.c -o kernel.o
# Link boot.S, kernel.c
arm-none-eabi-gcc -T linker.ld -o myos.elf -ffreestanding -O2 -nostdlib boot.o kernel.o

# Run with qemu-system-arm (for Raspberry Pi 2)
qemu-system-arm -m 256 -M raspi2 -serial stdio -kernel myos.elf