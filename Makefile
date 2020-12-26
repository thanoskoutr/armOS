CC=arm-none-eabi-gcc

# We have to check for model
CPU=cortex-a7

SFLAGS=-mcpu=$(CPU) -fpic -ffreestanding
CFLAGS=-O2 -Wall -Wextra
LFLAGS=-ffreestanding -O2 -nostdlib

BUILD_DIR = build
SRC_DIR = src

IMG_NAME=kernel.img

all: build

# Make targets for all .o, .c files

boot.o: boot.S
	$(CC) $(SFLAGS) -c $< -o $@

kernel.o: kernel.c
	$(CC) $(SFLAGS) $(CFLAGS) -c $< -o $@

build: boot.o kernel.o
	$(CC) -T linker.ld -o $(IMG_NAME) $(LFLAGS) $^

run: build
	# Run for Raspberry Pi 2
	qemu-system-arm -m 256 -M raspi2 -serial stdio -kernel $(IMG_NAME)

clean:
	rm -f *.o *.img