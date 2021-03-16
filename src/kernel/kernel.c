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
#include <kernel/console.h>
#include <kernel/mmio.h>
#include <kernel/scheduler.h>
#include <kernel/fork.h>

#include <common/string.h>
#include <common/stdlib.h>
#include <common/stdbool.h>

#ifdef AARCH_32
#include <armv6/irq.h>
#elif AARCH_64
#include <armv8-a/irq.h>
#endif

void process(char *array);

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
	char device[DEVICE_LENGTH];

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
	// printk("Initializing Timers...");
	// timer_1_init(6000);
	// timer_3_init(3000);
	// printk("Done\n");

	/* LED */
	printk("Initializing LED...");
	led_init(LED_PIN);
	printk("Done\n");

	/* Console */
	// console(device);

	/* Scheduler */
	printk("Initializing Timer 3...");
	timer_3_init(2000); /* Initialize Timer 3 for scheduler */
	printk("Done\n");

	/* Creates process 1 */
	printk("--- DEBUG: Forking process 1...");
#ifdef AARCH_32
	int res = copy_process((uint32_t) &process, (uint32_t) "12345");
#elif AARCH_64
	int res = copy_process((uint64_t) &process, (uint64_t) "12345");
#endif
	if (res != 0) {
		printk("Error while starting process 1\n");
		return;
	}
	printk("Done\n");

	/* Creates process 2 */
	printk("--- DEBUG: Forking process 2...");
#ifdef AARCH_32
	res = copy_process((uint32_t) &process, (uint32_t) "abcde");
#elif AARCH_64
	res = copy_process((uint64_t) &process, (uint64_t) "abcde");
#endif
	if (res != 0) {
		printk("Error while starting process 2\n");
		return;
	}
	printk("Done\n");

	printk("--- DEBUG: Entering in scheduling mode...\n");
	while(1) {
		/*
		 * Core scheduler function.
		 * Checks whether there is a new task,
		 * that needs to preempt the current one.
		 */
		schedule();
	}

	// while (1) {
	// 	/* Read from serial (dummy) */
	// 	unsigned char c = uart_getc();
	// 	if (c == '\r') {
	// 		/* When user presses Enter a CR is returned */
	// 		uart_putc(c);
	// 		uart_putc('\n');
	// 	}
	// 	else {
	// 		uart_putc(c);
	// 	}
	// }

}


/*
 * Dummy function that simulated a process.
 * It just prints the items of its array.
 */
void process(char *array)
{
	while (1) {
		for (int i = 0; i < 5; i++) {
			printk("%c", array[i]);
			delay(100000);
		}
	}
}