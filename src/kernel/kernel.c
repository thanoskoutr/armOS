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
#include <common/stdbool.h>

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

	char s[21];
	char c = 'x';
	int num = 20;
	memset(s, c, num);
	s[20] = '\0';
	printk("memset(s, %c, %d) = %s\n", c, num, s);

	char src[20];
	strcpy(src, "HeyManWhazup");
	int src_len = strlen(src);
	char dest[100];
	memcpy(dest, src, src_len + 1);
	printk("memcpy(dest, %s, %d) = %s\n", src, src_len + 1, dest);

	printk("strlen(%s) = %d\n", "HelloWorld", strlen("HelloWorld"));

	char sdest[200];
	printk("strcpy(sdest, _HeyAgainMan__ !) = ");
	strcpy(sdest, "_HeyAgainMan__ !");
	printk("%s\n", sdest);

	char ch2[100];
	strcpy(ch2, "HelloKernelWorld");
	printk("strrev(%s) = ", ch2);
	strrev(ch2);
	printk("%s\n", ch2);

	char s1[50];
	char s2[50];
	strcpy(s1, "_HeyAgainMan__ !");
	strcpy(s2, "_HEYAGAINMAN__");
	printk("strcmp(%s, %s) = %d\n", s1, s2, strcmp(s1, s2));
	strcpy(s1, "_HeyAgainMan__ !");
	strcpy(s2, "smaller_str");
	printk("strcmp(%s, %s) = %d\n", s1, s2, strcmp(s1, s2));
	strcpy(s1, "_HeyAgainMan__ !");
	strcpy(s2, "_HeyAgainMan__ !");
	printk("strcmp(%s, %s) = %d\n", s1, s2, strcmp(s1, s2));

	strcpy(s1, "I want to be...");
	strcpy(s2, "concatinated!!");
	printk("strcat(%s, %s) = ", s1, s2);
	strcat(s1, s2);
	printk("%s\n", s1);

	printk("\n----- Done Testing string.h, stdlib.h -----\n\n");

	printk("\n----- Testing stdbool.h -----\n\n");
	bool a = true;
	bool b = false;

	printk("a = %d, b = %d\n", a, b);
	printk("a || b = %d\n", a || b);
	printk("a && b = %d\n", a && b);
	printk("!a = %d\n", !a);
	printk("!b = %d\n", !b);
	printk("a == b = %d\n", a == b);
	printk("a != b = %d\n", a != b);

	printk("\n----- Done Testing stdbool.h-----\n\n");


	while (1) {
		uart_putc(uart_getc());
	}

}