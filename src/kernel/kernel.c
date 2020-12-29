#include <stddef.h>
#include <stdint.h>
#include <kernel/uart.h>

/* Arguments for AArch32 */
void kernel_main(uint32_t r0, uint32_t r1, uint32_t atags)
/* arguments for AArch64 */
// void kernel_main(uint64_t dtb_ptr32, uint64_t x1, uint64_t x2, uint64_t x3)
{
	/* Declare as unused */
	(void) r0;
	(void) r1;
	(void) atags;

	uart_init();
	uart_puts("Hello, beautiful kernel World!\r\n");

	while (1) {
		uart_putc(uart_getc());
		uart_putc('\n');
	}

}