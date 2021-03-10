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
    - [x] Kernel starts at EL2
    - [x] Print EL
    - [x] Change from EL2 to EL1
- [x] Starts kernel at `0x0` instead of `0x80000`