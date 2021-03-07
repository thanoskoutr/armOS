/*
 * kernel.c - Main kernel function
 * Code for Raspberry Pi
 */

#include <stddef.h>
#include <stdint.h>
#include <kernel/uart.h>

/* Arguments for AArch32 */
// void kernel_main(uint32_t r0, uint32_t r1, uint32_t atags)
/* arguments for AArch64 */
// void kernel_main(uint64_t dtb_ptr32, uint64_t x1, uint64_t x2, uint64_t x3)

void kernel_main()
{
	/* Declare as unused */
	// (void) r0;
	// (void) r1;
	// (void) atags;

	uart_init();

	/* Print Initial Starting Message to Serial Console */
	uart_puts("\r\n");
	uart_puts("                  _____ _____ \r\n");
	uart_puts(" ___ ___ _____   |     |   __|\r\n");
	uart_puts("| . |  _|     |  |  |  |__   |\r\n");
	uart_puts("|__,|_| |_|_|_|  |_____|_____|\r\n");

	uart_puts("\r\nCustom ARM OS initializing...\r\n");

#ifdef MODEL_0
	uart_puts("\r\n\tBoard: Raspberry Pi Zero / Zero W\r\n");
#elif MODEL_2
	uart_puts("\r\n\tBoard: Raspberry Pi 2\r\n");
#elif MODEL_3
	uart_puts("\r\n\tBoard: Raspberry Pi 3\r\n");
#elif MODEL_4
	uart_puts("\r\n\tBoard: Raspberry Pi 4\r\n");
#endif

#ifdef AARCH_32
	uart_puts("\tArch: aarch32\r\n");
#elif AARCH_64
	uart_puts("\tArch: aarch64\r\n");
#endif
	uart_puts("Done\r\n");


	while (1) {
		uart_putc(uart_getc());
	}

}