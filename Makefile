CC = arm-none-eabi-gcc
OBJCOPY = arm-none-eabi-objcopy
CC_64 = aarch64-none-elf-gcc
OBJCOPY_64 = aarch64-none-elf-objcopy

SFLAGS = -mcpu=$(CPU) -fpic -ffreestanding -nostdlib -nostartfiles $(DIRECTIVES)
CFLAGS = -O2 -Wall -Wextra
LDFLAGS = -ffreestanding -O2 -nostdlib

IMG_NAME=kernel7.img
IMG_NAME_64=kernel8.img

ifeq ($(RASPI_MODEL), 0)
	CPU = arm1176jzf-s
	DIRECTIVES = -D MODEL_0
	ARCH_DIR = arch/raspberrypi0
else ifeq ($(RASPI_MODEL), 2)
	CPU = cortex-a7
	DIRECTIVES = -D MODEL_2
	ARCH_DIR = arch/raspberrypi2
else ifeq ($(RASPI_MODEL), 3)
	## AS IS runs aarch64 code
	SFLAGS = -mgeneral-regs-only $(DIRECTIVES)
	# CPU = cortex-a7
	# SFLAGS += -mgeneral-regs-only -nostartfiles
	DIRECTIVES = -D MODEL_3
	ARCH_DIR = arch/raspberrypi-64bit
	# ARCH_DIR = arch/raspberrypi2
	CC = aarch64-none-elf-gcc
else ifeq ($(RASPI_MODEL), 4)
	SFLAGS = -mgeneral-regs-only $(DIRECTIVES)
	DIRECTIVES = -D MODEL_4
	ARCH_DIR = arch/raspberrypi-64bit
	CC = aarch64-none-elf-gcc
endif

BUILD_DIR = build
SRC_DIR = src
INC_DIR = include

KER_SRC = src/kernel
COMMON_SRC = src/common

.PHONY: clean all build

all: build

# ! Rename obj files -> *_c.o, *_s.o
# ! Make targets for all .o, .c files

$(BUILD_DIR)/boot.o: $(ARCH_DIR)/boot.S
	mkdir -p $(@D)
	$(CC) $(SFLAGS) -c $< -o $@

$(BUILD_DIR)/kernel.o: $(KER_SRC)/kernel.c
	$(CC) $(SFLAGS) $(CFLAGS) -I$(INC_DIR) -c $< -o $@

$(BUILD_DIR)/uart.o: $(KER_SRC)/uart.c
	$(CC) $(SFLAGS) $(CFLAGS) -I$(INC_DIR) -c $< -o $@

build: $(BUILD_DIR)/boot.o $(BUILD_DIR)/uart.o $(BUILD_DIR)/kernel.o

ifeq ($(ARCH_DIR), arch/raspberrypi-64bit)
	$(CC) -T $(KER_SRC)/linker.ld -o $(IMG_NAME) $(LDFLAGS) $^
	$(OBJCOPY_64) -O binary $(IMG_NAME) $(IMG_NAME_64)
else
	$(CC) -T $(KER_SRC)/linker.ld -o $(IMG_NAME) $(LDFLAGS) $^
	$(OBJCOPY) -O binary $(IMG_NAME) $(IMG_NAME)
endif


run2: build
	# Run for Raspberry Pi 2
	qemu-system-arm -m 256 -M raspi2 -serial stdio -kernel $(IMG_NAME)

run0: build
	# Run for Raspberry Pi Zero
	qemu-system-arm -cpu arm1176 -m 256 -M versatilepb -serial stdio -kernel $(IMG_NAME)

run3: build
	# Run for Raspberry Pi 3
	qemu-system-aarch64 -M raspi3 -serial stdio -kernel $(IMG_NAME_64)
	# qemu-system-aarch64 -M raspi3 -serial stdio -kernel $(IMG_NAME)

clean:
	rm -rf $(BUILD_DIR) *.img
	# rm -f $(BUILD_DIR)/*.o *.img