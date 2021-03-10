/*
 * irq.S - Implementation of armv8-a interrupt initialization functions.
 */

/*
 * Initializes interrupts, by setting the address of the Vector Base Address
 * 	Register (vbar_el1) to our vector table address.
 */
.globl irq_vector_init
irq_vector_init:
	adr x0, vectors		/* load VBAR_EL1 with virtual */
	msr vbar_el1, x0	/* vector table address */
	ret

/*
 * Enables (Unmasks) interrupts.
 */
.globl irq_enable
irq_enable:
	msr daifclr, #2		/* Unmask IRQs */
	ret

/*
 * Disables (Masks) interrupts.
 */
.globl irq_disable
irq_disable:
	msr daifset, #2		/* Mask IRQs */
	ret

/*
 * DAIF{clr,set}:
 *	D: Un/Masks debug exceptions	(Bit 0)
 *	A: Un/Masks SErrors		(Bit 1)
 *	I: Un/Masks IRQs		(Bit 2)
 *	F: Un/Masks FIQs		(Bit 3)
 */