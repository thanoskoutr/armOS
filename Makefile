CC = arm-none-eabi-gcc

# We have to check for model
CPU = cortex-a7

SFLAGS = -mcpu=$(CPU) -fpic -ffreestanding
CFLAGS = -O2 -Wall -Wextra
LFLAGS = -ffreestanding -O2 -nostdlib

BUILD_DIR = build
SRC_DIR = src
KER_SRC = src/kernel
KER_HEAD = include
COMMON_SRC = src/common

IMG_NAME=kernel.img

all: build

# ! Make targets for all .o, .c files

$(BUILD_DIR)/boot.o: $(KER_SRC)/boot.S
	$(CC) $(SFLAGS) -c $< -o $@

$(BUILD_DIR)/kernel.o: $(KER_SRC)/kernel.c
	$(CC) $(SFLAGS) $(CFLAGS) -c $< -o $@

build: $(BUILD_DIR)/boot.o $(BUILD_DIR)/kernel.o
	$(CC) -T $(KER_SRC)/linker.ld -o $(IMG_NAME) $(LFLAGS) $^

run: build
	# Run for Raspberry Pi 2
	qemu-system-arm -m 256 -M raspi2 -serial stdio -kernel $(IMG_NAME)

clean:
	rm -f $(BUILD_DIR)/*.o *.img