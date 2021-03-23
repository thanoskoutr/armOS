/*
 * utils.S - Implementation of basic armv8-a assembly functions.
 */

/*
 * Gets the Exception Level of the processor (ARMv-8)
 */
.globl get_el
get_el:
	mrs x0, CurrentEL
	lsr x0, x0, #2
	ret
/*
 * Zeroes out the section defined by the starting address on x0
 * and the size of the section on x1.
 */
.globl memzero
memzero:
	str xzr, [x0], #8	/* Stores a zero value (xzr) to x0 */
	subs x1, x1, #8		/* Decrease the section to be cleared */
	b.gt memzero		/* Until its 0, so we return */
	ret