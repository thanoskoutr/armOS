/*
 * boot.S - Assembly Startup Code
 * AArch64 mode
 * Code for Raspberry Pi 3, 4
 */

#include <armv8-a/mm.h>
#include <armv8-a/sysregs.h>

// To keep this in the first portion of the binary
.section ".text.boot"

.global _start

/*
 * Entry point for the kernel
 * x0 -> 32 bit pointer to DTB in memory (primary core only) / 0 (secondary cores)
 * x1 -> 0
 * x2 -> 0
 * x3 -> 0
 * x4 -> 32 bit kernel entry point, _start location
 * Preserve these registers as argument for kernel_main
 */

_start:
	/* Check if processor ID is zero (executing on main core), else hang */
	mrs x0, mpidr_el1
	and x0, x0, #0xFF	// Check processor id
	cbz x0, master		// Hang for all non-primary CPU
	b proc_hang
	/* We are not on the main core, so hang in an infinite wait loop */
proc_hang:
	wfe
	b proc_hang

master:
	/* System Control Register (SCTLR)
	 * Configuring different parameters for the processor.
	 * See <armv8-a/sysregs.h> for configuration.
	 */
	ldr x0, =SCTLR_VALUE_MMU_DISABLED
	msr sctlr_el1, x0


	/* Hypervisor Configuration Register (HCR)
	 * Setting execution state at EL1 to be AArch64.
	 */
	ldr x0, =HCR_VALUE
	msr hcr_el2, x0

	/* Saved Program Status Register (SPSR)
	 * Preparing processor state.
	 * See <armv8-a/sysregs.h> for configuration.
	 */
	ldr x0, =SPSR_VALUE
	msr spsr_el2, x0

	/* Exception Link Register (ELR)
	 * Holds the address, to which we are going to return
	 * after eret instruction will be executed.
	 * Here we set this address to the location of el1_entry label.
	 */
	adr x0, el1_entry
	msr elr_el2, x0

	eret

	/* Code executing only by main core (cpu id == 0) */
el1_entry:
	/*
	 * With the latest firmware, only the primary core runs (core 0), and
	 * the secondary cores are awaiting in a spin loop.
	 */
	mov sp, #LOW_MEMORY		// Setup the stack at 4 MB (64 bit).

	ldr x5, =__bss_start		// Clear out BSS.
	ldr w6, =__bss_size
clear_bss:
	cbz w6, kernel_entry
	str xzr, [x5], #8
	sub w6, w6, #1
	cbnz w6, clear_bss

kernel_entry:
	bl kernel_main			// Call kernel_main (C Code).
					// Should not return from here.

	b proc_hang			// For failsafe, halt this core too.

