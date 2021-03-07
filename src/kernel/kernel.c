/*
 * kernel.c - Main kernel function
 * Code for Raspberry Pi
 */

#include <stddef.h>
#include <stdint.h>
#include <kernel/uart.h>

#include <common/stdio.h>
#include <common/printf.h>

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

	/* Initialize UART */
	uart_init();

	/* Initialize printf to to use putc (the character output function) */
	init_printf(NULL, putc);

	/* Print Initial Starting Message to Serial Console */
	uart_puts("\n");
	uart_puts("                  _____ _____ \n");
	uart_puts(" ___ ___ _____   |     |   __|\n");
	uart_puts("| . |  _|     |  |  |  |__   |\n");
	uart_puts("|__,|_| |_|_|_|  |_____|_____|\n");

	uart_puts("\nCustom ARM OS initializing...\n");

#ifdef MODEL_0
	uart_puts("\n\tBoard: Raspberry Pi Zero / Zero W\n");
#elif MODEL_2
	uart_puts("\n\tBoard: Raspberry Pi 2\n");
#elif MODEL_3
	uart_puts("\n\tBoard: Raspberry Pi 3\n");
#elif MODEL_4
	uart_puts("\n\tBoard: Raspberry Pi 4\n");
#endif

#ifdef AARCH_32
	uart_puts("\tArch: aarch32\n");
#elif AARCH_64
	uart_puts("\tArch: aarch64\n");
#endif
	uart_puts("Done\n");

	printf("Testing printf(): New line + Type support\r\n");
	printf("Test int: %d\r\n", 1);
	int x = 5;
	printf("Test int var: %d\r\n", x);
	printf("Test hex: %x\r\n", 0x1A);
	printf("Test char: %c\r\n", 'a');
	printf("Test string: %s\r\n", "this is a string");


	while (1) {
		uart_putc(uart_getc());
	}

}