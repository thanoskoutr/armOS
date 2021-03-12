/*
 * irq.S - Implementation of armv6 interrupt initialization functions.
 */

/*
 * Initializes interrupts, by moving the exception vector at address 0x0
 */
.globl irq_vector_init
irq_vector_init:
	push {r4, r5, r6, r7, r8, r9}	/* Save registers from C caller function */
	ldr r0, =vectors		/* Loads address of vectors into r0. */
	mov r1, #0x0000			/* r1 is the destination register */
	/* Load data from vectors (8 addresses), in r2-r9 */
	ldmia r0!, {r2, r3, r4, r5, r6, r7, r8, r9}
	/* Store data from vectors (registers r2-r9 values) into address 0x0 */
	stmia r1!, {r2, r3, r4, r5, r6, r7, r8, r9}
	/* Load absolute addresses (after vectors), in r2-r9 */
	ldmia r0!, {r2, r3, r4, r5, r6, r7, r8, r9}
	/* Store absolute addresses (registers r2-r9 values) after vectors */
	stmia r1!, {r2, r3, r4, r5, r6, r7, r8, r9}
	pop {r4, r5, r6, r7, r8, r9}	/* Restore caller's registers */
	blx lr				/* Return to caller */

/*
 * Enables (Unmasks) interrupts.
 */
.globl irq_enable
irq_enable:
	/* Store CPSR (Current Program Status Register) */
	mrs r0, cpsr
	/* Check bit 7. If bit 7 is clear, then interrupts are enabled, exit */
	tst r0, #0x80
	bxeq lr
	/* Enable IRQs */
	cpsie i
	bx lr


/*
 * Disables (Masks) interrupts.
 */
.globl irq_disable
irq_disable:
	/* Store CPSR (Current Program Status Register) */
	mrs r0, cpsr
	/* Check bit 7. If bit 7 is set, then interrupts are disabled, exit */
	tst r0, #0x80
	bxne lr
	/* Disable IRQs */
	cpsid i
	bx lr