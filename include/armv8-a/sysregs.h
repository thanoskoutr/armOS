/*
 * sysregs.h - Definition of armv8-a system registers
 * Needed for Exception level change.
 */

#ifndef SYSREGS_H
#define SYSREGS_H

/*
 * SCTLR_EL1, System Control Register (EL1)
 * Page 2654 of AArch64-Reference-Manual.
 */

#define SCTLR_RESERVED		(3 << 28) | (3 << 22) | (1 << 20) | (1 << 11)
#define SCTLR_EE_LITTLE_ENDIAN	(0 << 25)
#define SCTLR_EOE_LITTLE_ENDIAN	(0 << 24)
#define SCTLR_I_CACHE_DISABLED	(0 << 12)
#define SCTLR_D_CACHE_DISABLED	(0 << 2)
#define SCTLR_MMU_DISABLED	(0 << 0)
#define SCTLR_MMU_ENABLED	(1 << 0)
#define SCTLR_VALUE_MMU_DISABLED	(SCTLR_RESERVED | \
 		SCTLR_EE_LITTLE_ENDIAN | SCTLR_I_CACHE_DISABLED | \
 		SCTLR_D_CACHE_DISABLED | SCTLR_MMU_DISABLED)

/*
 * SCTLR_RESERVED: 		Reserved bits are initialized to 1.
 * SCTLR_EE_LITTLE_ENDIAN:	Work only with little-endian format at EL1.
 * SCTLR_EOE_LITTLE_ENDIAN: 	Work only with little-endian format at EL0.
 * SCTLR_I_CACHE_DISABLED: 	Disable instruction cache.
 * SCTLR_D_CACHE_DISABLED: 	Disable data cache.
 * SCTLR_MMU_DISABLED: 		Disable MMU.
 */



/*
 * HCR_EL2, Hypervisor Configuration Register (EL2)
 * Page 2487 of AArch64-Reference-Manual.
 */

#define HCR_RW			(1 << 31)
#define HCR_VALUE		HCR_RW

/*
 * HCR_RW: Sets execution state to be AArch64.
 */



/*
 * SPSR_EL3, Saved Program Status Register (EL3)
 * Page 389 of AArch64-Reference-Manual.
 */

#define SPSR_MASK_ALL 		(7 << 6)
#define SPSR_EL1h		(5 << 0)
#define SPSR_VALUE		(SPSR_MASK_ALL | SPSR_EL1h)

/*
 * SPSR_MASK_ALL: 	After we change EL to EL1 all types of interrupts
 * 			will be masked (disabled).
 * SPSR_EL1h:		EL1h mode: We are using EL1 dedicated stack pointer.
 */

#endif