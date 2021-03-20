# Set Compiler flags
SFLAGS = -mcpu=$(CPU) -fpic -ffreestanding -nostdlib -nostartfiles $(DIRECTIVES)
CFLAGS = -O2 -Wall -Wextra -g
LDFLAGS = -ffreestanding -O2 -nostdlib

# Set Cross-Compiler Toolchain
ARMGNU = arm-none-eabi
ARMGNU_64 = aarch64-none-elf

# Set kernel image name
IMG_NAME = kernel7
IMG_NAME_64 = kernel8

# Set Raspi Model, if not set
# RASPI_MODEL ?= 0
RASPI_MODEL ?= 4

# Set flags and variables dependent on the Raspi Model
ifeq ($(RASPI_MODEL), 0)
	AARCH = AARCH_32
	MODEL = MODEL_0
	ARCH_DIR = arch/armv6
	CPU = arm1176jzf-s
	DIRECTIVES = -D $(MODEL) -D $(AARCH)
else ifeq ($(RASPI_MODEL), 2)
	AARCH = AARCH_32
	MODEL = MODEL_2
	ARCH_DIR = arch/armv7-a
	CPU = cortex-a7
	DIRECTIVES = -D $(MODEL) -D $(AARCH)
else ifeq ($(RASPI_MODEL), 3)
	AARCH = AARCH_64
	MODEL = MODEL_3
	ARCH_DIR = arch/armv8-a
	SFLAGS += -mgeneral-regs-only
	DIRECTIVES = -D $(MODEL) -D $(AARCH)
	ARMGNU = $(ARMGNU_64)
	IMG_NAME = $(IMG_NAME_64)
else ifeq ($(RASPI_MODEL), 4)
	AARCH = AARCH_64
	MODEL = MODEL_4
	ARCH_DIR = arch/armv8-a
	SFLAGS += -mgeneral-regs-only
	CPU = cortex-a72
	DIRECTIVES = -D $(MODEL) -D $(AARCH)
	ARMGNU = $(ARMGNU_64)
	IMG_NAME = $(IMG_NAME_64)
endif

# Set Build / Source / Include / Docs directories
BUILD_DIR = build
SRC_DIR = src
INC_DIR = include
DOCS_DIR = docs

KER_SRC = src/kernel
COMMON_SRC = src/common

KERNEL_VERSION = 0.1.0

.PHONY: clean all build docs docs_pdf clean_docs

all: build

# Compile project
## Compile every asm file in /arch/$(ARCH_DIR)
$(BUILD_DIR)/%_s.o: $(ARCH_DIR)/%.S
	mkdir -p $(@D)
	$(ARMGNU)-gcc $(SFLAGS) $(CFLAGS) -I$(INC_DIR) -c $< -o $@

## Compile every C file in /src/kernel
$(BUILD_DIR)/%_c.o: $(KER_SRC)/%.c
	mkdir -p $(@D)
	$(ARMGNU)-gcc $(SFLAGS) $(CFLAGS) -I$(INC_DIR) -c $< -o $@

## Compile every C file in /src/common
$(BUILD_DIR)/%_c.o: $(COMMON_SRC)/%.c
	mkdir -p $(@D)
	$(ARMGNU)-gcc $(SFLAGS) $(CFLAGS) -I$(INC_DIR) -c $< -o $@

## Find all object files (from corresponding C, asm files)
ASM_FILES = $(wildcard $(ARCH_DIR)/*.S)
KER_C_FILES = $(wildcard $(KER_SRC)/*.c)
COMMON_C_FILES = $(wildcard $(COMMON_SRC)/*.c)

OBJ_FILES = $(ASM_FILES:$(ARCH_DIR)/%.S=$(BUILD_DIR)/%_s.o)
OBJ_FILES += $(KER_C_FILES:$(KER_SRC)/%.c=$(BUILD_DIR)/%_c.o)
OBJ_FILES += $(COMMON_C_FILES:$(COMMON_SRC)/%.c=$(BUILD_DIR)/%_c.o)

## Link all object files and create final image
build: $(OBJ_FILES)
	@echo "----- Building for Raspberry Pi $(value RASPI_MODEL) -----"
	@echo "----- Building for $(value AARCH) -----"

	$(ARMGNU)-gcc -T $(ARCH_DIR)/linker.ld -o $(IMG_NAME).elf $(LDFLAGS) $^
	$(ARMGNU)-objcopy -O binary $(IMG_NAME).elf $(IMG_NAME).img


# Compile armstub
STUB_DIR = armstub
STUB_FILES = $(wildcard ${STUB_DIR}/$(SRC_DIR)/*.S)
OBJ_STUB_FILES = $(STUB_FILES:${STUB_DIR}/$(SRC_DIR)/%.S=${STUB_DIR}/$(BUILD_DIR)/%_s.o)

## Compile armstub in /armstub/src
$(STUB_DIR)/$(BUILD_DIR)/%_s.o: $(STUB_FILES)
	mkdir -p $(@D)
	$(ARMGNU)-gcc $(SFLAGS) $(CFLAGS) -c $< -o $@

armstub: $(OBJ_STUB_FILES)
	$(ARMGNU)-ld --section-start=.text=0 -o ${STUB_DIR}/$(BUILD_DIR)/armstub.elf $<
	$(ARMGNU)-objcopy ${STUB_DIR}/$(BUILD_DIR)/armstub.elf -O binary armstub-new.bin


# Generating Documentation
## Docs directories and config file
DOXYGEN_DIR = $(DOCS_DIR)/doxygen
DOXYFILE = .doxygenconfig

## Rule for genereting docs with doxygen
docs:
	( cat $(DOXYFILE) ;                                \
	echo "PREDEFINED = $(MODEL) $(AARCH)" ;            \
	echo "OUTPUT_DIRECTORY = $(DOXYGEN_DIR)" ;         \
	echo "INPUT = $(SRC_DIR) $(INC_DIR)" ;             \
	echo "PROJECT_NUMBER = $(KERNEL_VERSION)" )        \
	| doxygen -

docs_pdf:
	( cd $(DOXYGEN_DIR)/latex; pdflatex refman.tex ; \
	echo "\nThe PDF reference manual is located at $(DOXYGEN_DIR)/latex/refman.pdf" )

# Rules for running on QEMU (not working)
run2: build
	# Run for Raspberry Pi 2
	qemu-system-arm -m 256 -M raspi2 -serial stdio -kernel $(IMG_NAME).img

run0: build
	# Run for Raspberry Pi Zero
	qemu-system-arm -cpu arm1176 -m 256 -M versatilepb -serial stdio -kernel $(IMG_NAME).img

run3: build
	# Run for Raspberry Pi 3
	qemu-system-aarch64 -M raspi3 -serial stdio -kernel $(IMG_NAME).img


# Clean rules
clean:
	rm -rf $(BUILD_DIR) *.img *.elf *.bin $(STUB_DIR)/$(BUILD_DIR)

clean_docs:
	rm -rf $(DOXYGEN_DIR)