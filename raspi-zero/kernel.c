#include <stddef.h>
#include <stdint.h>
#include <uart.h>

/* For Blinking LED */
#define GPFSEL3 0x2020000C
#define GPFSEL4 0x20200010
#define GPSET1  0x20200020
#define GPCLR1  0x2020002C

/* Arguments for AArch32 */
void kernel_main(uint32_t r0, uint32_t r1, uint32_t atags)
{
	/* Declare as unused */
	(void) r0;
	(void) r1;
	(void) atags;

	// unsigned int ra;

	/* Print string to terminal */
	uart_init();
	uart_puts("Hello, beautiful kernel World!\r\n");

	/* Blink LED */
	// ra = mmio_read(GPFSEL4);
	// ra &= ~(7 << 21);
	// ra |= 1 << 21;
	// mmio_write(GPFSEL4, ra);

	// while (1) {
	// 	mmio_write(GPSET1, 1 << (47-32));
	// 	delay(0x100000);
	// 	mmio_write(GPCLR1, 1 << (47-32));
	// 	delay(0x100000);
	// }

	/* Bad echo, thats always prints new line */
	while (1) {
		uart_putc(uart_getc());
		// uart_putc('\n');
	}

}