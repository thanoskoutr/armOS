/*
 * boot.S - Assembly Startup Code
 * AArch32 mode
 * Code for Raspberry Pi 2
 */

@ To keep this in the first portion of the binary
.section ".text.boot"

.global _start

/*
 * Entry point for the kernel
 * pc -> Should begin execution at 0x8000
 * r0 -> 0
 * r1 -> Machine ID
 * r2 -> Start of ATAGS
 * Preserve these registers as argument for kernel_main
 */

_start:
	mov sp, #0x8000			@ Setup the stack.

	ldr r4, =__bss_start		@ Clear out BSS.
	ldr r9, =__bss_end
	mov r5, #0
	mov r6, #0
	mov r7, #0
	mov r8, #0
	b 	2f			@ Unconditional jump forward to label 2.

	/*
	 * Store multiple, Increment after, Store incremented address back:
	 * mem32[r4 + 0] := r5
	 * mem32[r4 + 4] := r6
	 * mem32[r4 + 8] := r7
	 * mem32[r4 + 12] := r8
	 */
1:
	stmia r4!, {r5-r8}		@ Store multiple at r4 address.

2:
	cmp r4, r9			@ If we are still below bss_end,
	blo 1b				@ loop backwards to label 1.

	ldr r3, =kernel_main		@ Call kernel_main (C Code).
	blx r3				@ Should not return from here.

halt:
	wfe				@ Wait For Event.
	b halt				@ For failsafe, halt this core too.

