CC = arm-none-eabi-gcc
OBJCOPY = arm-none-eabi-objcopy

CPU = arm1176jzf-s
DIRECTIVES = -D MODEL_0

SFLAGS = -mcpu=$(CPU) -fpic -ffreestanding -nostdlib -nostartfiles $(DIRECTIVES)
CFLAGS = -O2 -Wall -Wextra
LDFLAGS = -ffreestanding -O2 -nostdlib

IMG_NAME=kernel.img

BUILD_DIR = build
INC_DIR = include

.PHONY: clean all build

all: build

$(BUILD_DIR)/boot.o: boot.S
	mkdir -p $(@D)
	$(CC) $(SFLAGS) -c $< -o $@

$(BUILD_DIR)/kernel.o: kernel.c
	$(CC) $(SFLAGS) $(CFLAGS) -I$(INC_DIR) -c $< -o $@

$(BUILD_DIR)/uart.o: uart.c
	$(CC) $(SFLAGS) $(CFLAGS) -I$(INC_DIR) -c $< -o $@

build: $(BUILD_DIR)/boot.o $(BUILD_DIR)/uart.o $(BUILD_DIR)/kernel.o
	$(CC) -T linker.ld -o $(IMG_NAME) $(LDFLAGS) $^
	$(OBJCOPY) -O binary $(IMG_NAME) $(IMG_NAME)

clean:
	rm -rf $(BUILD_DIR) *.img