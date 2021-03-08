/*
 * kernel.c - Main kernel function
 * Code for Raspberry Pi
 */

#include <stddef.h>
#include <stdint.h>
#include <kernel/uart.h>
#include <kernel/printk.h>
#include <common/string.h>
#include <common/stdlib.h>

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
	uart_puts("\n\n");
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

	/* Testing */
	printk("\n----- Testing printk -----\n\n");
	uart_puts("uart: 0x2a\n");
	printk("printk: %x\n", 0x2a);

	uart_puts("uart: hello 2232130 from s\n");
	printk("printk: hello %d from %c\n", 2232130, 's');

	printk("OK man, good %s, since %d\n", "job man", -29000);
	printk("We got 30%%\n");

	printk("\n----- Done Testing printk -----\n\n");

	printk("\n----- Testing string.h, stdlib.h -----\n\n");
	int x = -11299770;
	int y = 2147483647;
	printk("itoa(%d): %s\n", x, itoa(x));
	printk("itoa(%d): %s\n", y, itoa(y));

	printk("strlen(%s) = %d\n", "HelloWorld", strlen("HelloWorld"));
	/* Need to implement strcpy */
	// char ch1[100] = "HelloWorld";
	// printk("strlen(%s) = %d\n", ch1, strlen(ch1));

	// char ch2[100] = "HelloKernelWorld";
	// printk("strrev(%s) = ", ch2);
	// strrev(ch2);
	// printk("%s\n", ch2);
	printk("\n----- Done Testing string.h, stdlib.h -----\n\n");


	while (1) {
		uart_putc(uart_getc());
	}

}