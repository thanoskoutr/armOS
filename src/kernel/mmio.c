/*
 * mmio.c - Provides functions for reading and writing from/to Memory Mapped IO
 */

#include <kernel/mmio.h>

/*
 * Memory-Mapped I/O output
 */
#ifdef AARCH_32
void mmio_write(uint32_t reg, uint32_t data)
{
	*(volatile uint32_t*)reg = data;
}
#elif AARCH_64
void mmio_write(uint64_t reg, uint32_t data)
{
	*(volatile uint32_t*)reg = data;
}
#endif

/*
 * Memory-Mapped I/O input
 */
#ifdef AARCH_32
uint32_t mmio_read(uint32_t reg)
{
	return *(volatile uint32_t*)reg;
}
#elif AARCH_64
uint32_t mmio_read(uint64_t reg)
{
	return *(volatile uint32_t*)reg;
}
#endif

/*
 * Loop <count> times, so the compiler won't optimize away
 */
void delay(int32_t count)
{
	asm volatile("__delay_%=:\n"
			"subs %[count], %[count], #1\n"
			"bne __delay_%=\n"
			: "=r" (count)
			: [count] "0" (count)
			: "cc"
		);
}