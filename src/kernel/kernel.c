/*
 * kernel.c - Main kernel function
 * Code for Raspberry Pi
 */

#include <stddef.h>
#include <stdint.h>

#include <kernel/uart.h>
#include <kernel/printk.h>
#include <kernel/utils.h>
#include <kernel/irq.h>
#include <kernel/timer.h>
#include <kernel/led.h>

#include <common/string.h>
#include <common/stdlib.h>
#include <common/stdbool.h>

#ifdef AARCH_32
#include <armv6/irq.h>
#elif AARCH_64
#include <armv8-a/irq.h>
#endif

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

	/* String for device name */
	char device[5];

	/* mini UART */
	uart_init();

	/* Print Initial Starting Message to Serial Console */
	printk("\n\n");
	printk("                  _____ _____ \n");
	printk(" ___ ___ _____   |     |   __|\n");
	printk("| . |  _|     |  |  |  |__   |\n");
	printk("|__,|_| |_|_|_|  |_____|_____|\n");

	printk("\nCustom ARM OS initializing...\n");

	/* Board Info */
#ifdef MODEL_0
	strcpy(device, "pi-0");
	printk("\n\tBoard: Raspberry Pi Zero / Zero W\n");
#elif MODEL_2
	strcpy(device, "pi-2");
	printk("\n\tBoard: Raspberry Pi 2\n");
#elif MODEL_3
	strcpy(device, "pi-3");
	printk("\n\tBoard: Raspberry Pi 3\n");
#elif MODEL_4
	strcpy(device, "pi-4");
	printk("\n\tBoard: Raspberry Pi 4\n");
#endif

	/* Arch Info */
#ifdef AARCH_32
	printk("\tArch: aarch32\n");
#elif AARCH_64
	printk("\tArch: aarch64\n");
#endif
	printk("\n");

	/* Exception Levels */
#ifdef AARCH_32
#elif AARCH_64
	int el = get_el();
	printk("\n----- Exception level: EL%d -----\n", el);
#endif

	/* Interrupts */
	printk("Initializing IRQs...");
	irq_vector_init();
	printk("Done\n");
	printk("Enabling IRQ controllers...");
	enable_interrupt_controller();
	printk("Done\n");
	printk("Enabling IRQs...");
	irq_enable();
	printk("Done\n");

	/* Timer */
	printk("Initializing Timer...");
	timer_init();
	printk("Done\n");

	/* LED */
	/*
	 * Raspi Zero W -> GPIO 47 (ACT LED)
 	 * Raspi 3, 4   -> GPIO 17 (LED Connected on physical pin 11)
	 */
#ifdef AARCH_32
	#define LED_PIN 47
#elif AARCH_64
	#define LED_PIN 17
#endif
	printk("Initializing LED...");
	led_init(LED_PIN);
	printk("Done\n");

	/* Disable Interrupts */
	printk("Disabling IRQs...");
	irq_disable();
	printk("Done\n");

	/* Console */
	char *input;
	char prompt[11];

	/* Create prompt */
	strcpy(prompt, "root@");
	strcat(prompt, device);
	strcat(prompt, "#");

	printk("\n");
	printk("This is a minimal console, type 'help' to see the available commands. (Maximum Input Length: %d)\n", MAX_INPUT_LENGTH);

	while (1) {
		/* Print prompt */
		printk("%s ", prompt);
		/* Read from serial */
		input = uart_gets();
		printk("\n");
		printk("input: %s\n", input);

		/* Read from serial (dummy) */
		// unsigned char c = uart_getc();
		// if (c == '\r') {
		// 	/* When user presses Enter a CR is returned */
		// 	uart_putc(c);
		// 	uart_putc('\n');
		// }
		// else {
		// 	uart_putc(c);
		// }
	}

}