CC = arm-none-eabi-gcc

ifeq ($(RASPI_MODEL), 0)
	CPU = arm1176jzf-s
	DIRECTIVES = -D MODEL_0
	ARCH_DIR = arch/raspberrypi0
else
	# Currently Model 2 support only
	CPU = cortex-a7
	DIRECTIVES = -D MODEL_2
	ARCH_DIR = arch/raspberrypi2
endif

SFLAGS = -mcpu=$(CPU) -fpic -ffreestanding $(DIRECTIVES)
CFLAGS = -O2 -Wall -Wextra
LFLAGS = -ffreestanding -O2 -nostdlib

BUILD_DIR = build
SRC_DIR = src
INCL_DIR = include

KER_SRC = src/kernel
COMMON_SRC = src/common

IMG_NAME=kernel.img

all: build

# ! Make targets for all .o, .c files

$(BUILD_DIR)/boot.o: $(ARCH_DIR)/boot.S
	$(CC) $(SFLAGS) -c $< -o $@

$(BUILD_DIR)/kernel.o: $(KER_SRC)/kernel.c
	$(CC) $(SFLAGS) $(CFLAGS) -I$(INCL_DIR) -c $< -o $@

$(BUILD_DIR)/uart.o: $(KER_SRC)/uart.c
	$(CC) $(SFLAGS) $(CFLAGS) -I$(INCL_DIR) -c $< -o $@

build: $(BUILD_DIR)/boot.o $(BUILD_DIR)/uart.o $(BUILD_DIR)/kernel.o
	$(CC) -T $(KER_SRC)/linker.ld -o $(IMG_NAME) $(LFLAGS) $^

run: build
	# Run for Raspberry Pi 2
	qemu-system-arm -m 256 -M raspi2 -serial stdio -kernel $(IMG_NAME)

run0: build
	# Run for Raspberry Pi Zero
	qemu-system-arm -cpu arm1176 -m 256 -M versatilepb -serial stdio -kernel $(IMG_NAME)

clean:
	rm -f $(BUILD_DIR)/*.o *.img