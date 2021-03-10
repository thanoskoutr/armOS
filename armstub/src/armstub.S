/*
 * armstub.S - Stub Code to launch the kernel
 * AArch64 mode
 * Code for Raspberry Pi 3, 4
 */

/* Loads the location of our kernel and branches to it */
.globl _start
_start:
	ldr w0, kernel_entry32
	br x0

.ltorg

/*
 * The firmware needst to find this value in this exact location,
 * in order to consider it a valid armstub
 */
.org 0xf0
.globl stub_magic
stub_magic:
	.word 0x5afe570b

/* We define the stub version to be 0 */
.org 0xf4
.globl stub_version
stub_version:
	.word 0

/* We define the location of our kernel which it is located at address 0x0 */
.org 0xfc
.globl kernel_entry32
kernel_entry32:
	.word 0x0