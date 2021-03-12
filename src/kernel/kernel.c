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

#include <armv8-a/irq.h>

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
	printk("\n\tBoard: Raspberry Pi Zero / Zero W\n");
#elif MODEL_2
	printk("\n\tBoard: Raspberry Pi 2\n");
#elif MODEL_3
	printk("\n\tBoard: Raspberry Pi 3\n");
#elif MODEL_4
	printk("\n\tBoard: Raspberry Pi 4\n");
#endif

	/* Arch Info */
#ifdef AARCH_32
	printk("\tArch: aarch32\n");
#elif AARCH_64
	printk("\tArch: aarch64\n");
#endif
	printk("Done\n");

	/* Exception Levels */
#ifdef AARCH_32
#elif AARCH_64
	int el = get_el();
	printk("\n----- Exception level: EL%d -----\n", el);
#endif

	/* Interrupts */
#ifdef AARCH_32
#elif AARCH_64
	printk("Initializing IRQs...\n");
	irq_vector_init();
	printk("Done\n");
	printk("Enabling IRQ controllers...\n");
	enable_interrupt_controller();
	printk("Done\n");
	printk("Enabling IRQs...\n");
	irq_enable();
	printk("Done\n");

	/* Timer */
	printk("Initializing Timer...\n");
	timer_init();
	printk("Done\n");

	/* LED */
	/*
	 * LEDs
	 * Raspi Zero W -> GPIO 47 (ACT LED)
 	 * Raspi 3, 4   -> GPIO 17 (LED Connected on physical pin 11)
	 */
	printk("Initializing LED...\n");
	led_init(17);
	printk("Done\n");

	printk("Pulse LED for 1 sec...\n");
	led_pulse(17, 1000);
	printk("Done\n");

	printk("Pulse LED for 2 sec...\n");
	led_pulse(17, 2000);
	printk("Done\n");

	printk("Pulse LED for 2 sec...\n");
	led_pulse(17, 2000);
	printk("Done\n");

	printk("Pulse LED 10 times, for 0.5 sec...\n");
	led_blink_times(17, 10, 500);
	printk("Done\n");

	printk("Turn LED ON, for 5 sec\n");
	led_on(17);
	timer_msleep(5000);
	printk("Turn LED OFF\n");
	led_off(17);

	printk("LED SOS, with 0.2 sec time interval\n");
	led_blink_sos(17, 200);

#endif

	printk("\nType Something: \n");

	while (1) {
		/* Read from serial */
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