# Set Compiler flags
SFLAGS = -mcpu=$(CPU) -fpic -ffreestanding -nostdlib -nostartfiles $(DIRECTIVES)
CFLAGS = -O2 -Wall -Wextra
LDFLAGS = -ffreestanding -O2 -nostdlib

# Set Cross-Compiler Toolchain
ARMGNU = arm-none-eabi
ARMGNU_64 = aarch64-none-elf

# Set kernel image name
IMG_NAME = kernel7.img
IMG_NAME_64 = kernel8.img

# Set Raspi Model, if not set
RASPI_MODEL ?= 0

# Set flags and variables dependent on the Raspi Model
ifeq ($(RASPI_MODEL), 0)
	AARCH = AARCH_32
	ARCH_DIR = arch/raspberrypi0
	CPU = arm1176jzf-s
	DIRECTIVES = -D MODEL_0 -D $(AARCH)
else ifeq ($(RASPI_MODEL), 2)
	AARCH = AARCH_32
	ARCH_DIR = arch/raspberrypi2
	CPU = cortex-a7
	DIRECTIVES = -D MODEL_2 -D $(AARCH)
else ifeq ($(RASPI_MODEL), 3)
	AARCH = AARCH_64
	ARCH_DIR = arch/raspberrypi-64bit
	SFLAGS = -mgeneral-regs-only $(DIRECTIVES)
	DIRECTIVES = -D MODEL_3 -D $(AARCH)
	ARMGNU = $(ARMGNU_64)
	IMG_NAME = $(IMG_NAME_64)
else ifeq ($(RASPI_MODEL), 4)
	AARCH = AARCH_64
	ARCH_DIR = arch/raspberrypi-64bit
	SFLAGS = -mgeneral-regs-only $(DIRECTIVES)
	DIRECTIVES = -D MODEL_4 -D $(AARCH)
	ARMGNU = $(ARMGNU_64)
	IMG_NAME = $(IMG_NAME_64)
endif

# Set Build / Source / Include directories
BUILD_DIR = build
SRC_DIR = src
INC_DIR = include

KER_SRC = src/kernel
COMMON_SRC = src/common

# KERNEL_VERSION = 0.1.0

.PHONY: clean all build

all: build

# ! Rename obj files -> *_c.o, *_s.o
# ! Make targets for all .o, .c files

# Compile project
$(BUILD_DIR)/boot.o: $(ARCH_DIR)/boot.S
	mkdir -p $(@D)
	$(ARMGNU)-gcc $(SFLAGS) -c $< -o $@

$(BUILD_DIR)/kernel.o: $(KER_SRC)/kernel.c
	$(ARMGNU)-gcc $(SFLAGS) $(CFLAGS) -I$(INC_DIR) -c $< -o $@

$(BUILD_DIR)/uart.o: $(KER_SRC)/uart.c
	$(ARMGNU)-gcc $(SFLAGS) $(CFLAGS) -I$(INC_DIR) -c $< -o $@

build: $(BUILD_DIR)/boot.o $(BUILD_DIR)/uart.o $(BUILD_DIR)/kernel.o
	@echo "----- Building for Raspberry Pi $(value RASPI_MODEL) -----"
	@echo "----- Building for $(value AARCH) -----"

	$(ARMGNU)-gcc -T $(KER_SRC)/linker.ld -o $(IMG_NAME) $(LDFLAGS) $^
	$(ARMGNU)-objcopy -O binary $(IMG_NAME) $(IMG_NAME)


# Rules for running on QEMU
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