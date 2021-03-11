# minimARM-OS

## Boards
Support for:

- [x] Raspberry Pi Zero W
- [x] Raspberry Pi 4
## Features
- [x] Basic Directory Structure
- [x] Register Addresses
    - [x] GPIO
    - [x] AUX
- [x] mini UART
- [x] Kernel printing info on start up
- [x] `printk`
- [x] `string.h` functions
    - [x] `strlen`, `strcmp`, `strcpy`, `strcat`, `strrev`
    - [x] `memset`, `memcpy`
- [ ] `stdlib.h` functions
    - [x] `itoa`
- [x] `stdbool`
    - [x] `true`, `false`
- [x] Exception Levels (ARMv8-a)
    - [x] `armstub` starts kernel at EL3
    - [x] Kernel starts at EL3
    - [x] Print EL
    - [x] Change from EL3 to EL1
- [x] Interrupts - IRQ (ARMv8-a)
    - [x] Initialize vector table
    - [x] Enable / Disable interrupts
    - [x] IRQ registers
    - [x] Handle mini UART interrupts
    - [x] Handle Timer interrupts