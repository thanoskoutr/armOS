/**
 * @file kernel.c
 * @brief Main kernel function
 */

#include <stddef.h>
#include <stdint.h>

#include <kernel/uart.h>
#include <kernel/printk.h>
#include <kernel/irq.h>
#include <kernel/timer.h>
#include <kernel/led.h>
#include <kernel/console.h>

#include <common/string.h>

#include <kernel/mmio.h>
#include <kernel/sys.h>
#include <kernel/scheduler.h>
#include <kernel/fork.h>

#ifdef AARCH_32
#include <armv6/irq.h>
#elif AARCH_64
#include <armv8-a/utils.h>
#include <armv8-a/irq.h>
#endif

/* Arguments for AArch32 */
// void kernel_main(uint32_t r0, uint32_t r1, uint32_t atags)
/* arguments for AArch64 */
// void kernel_main(uint64_t dtb_ptr32, uint64_t x1, uint64_t x2, uint64_t x3)

#ifdef MODEL_0
	/** \mainpage Main Page
	 * Documentation generated for Aarch32 and Raspberry Pi Zero / Zero W.
	 */
#elif MODEL_2
	/** \mainpage Main Page
	 * Documentation generated for Aarch32 and Raspberry Pi 2.
	 */
#elif MODEL_3
	/** \mainpage Main Page
	 * Documentation generated for Aarch64 and Raspberry Pi 3.
	 */
#elif MODEL_4
	/** \mainpage Main Page
	 * Documentation generated for Aarch64 and Raspberry Pi 4.
	 */
#endif

void user_process1(char *array)
{
	char buf[2] = {0};
	while (1) {
		for (int i = 0; i < 5; i++) {
			buf[0] = array[i];
			call_sys_write(buf);
			delay(100000);
		}
	}
}

void user_process()
{
	char buf[30] = {0};
	strcpy(buf, "User process started\n");
	call_sys_write(buf);
	unsigned long stack = call_sys_malloc();
	if (stack < 0) {
		printk("Error while allocating stack for process 1\n");
		return;
	}
	int err = call_sys_clone((unsigned long) &user_process1, (unsigned long) "12345", stack);
	if (err < 0) {
		printk("Error while clonning process 1\n");
		return;
	}
	stack = call_sys_malloc();
	if (stack < 0) {
		printk("Error while allocating stack for process 1\n");
		return;
	}
	err = call_sys_clone((unsigned long) &user_process1, (unsigned long) "abcd", stack);
	if (err < 0) {
		printk("Error while clonning process 2\n");
		return;
	}
	call_sys_exit();
}

void kernel_process()
{
	printk("Kernel process started. EL %d\n", get_el());
	int err = move_to_user_mode((unsigned long) &user_process);
	if (err < 0){
		printk("Error while moving process to user mode\n");
	}
}

/**
 * Main kernel function.
 * @details Entry point for the kernel in C code after bootloader.
 * Main functionalities:
 * - Initializes devices, system:
 * 	- UART
 * 	- Interrupts
 * 	- LED
 * - Prints starting message and device info.
 * - Calls console(), in order to start and run a console.
 *
 * @see uart_init(), irq_vector_init(), enable_interrupt_controller(),
 *  irq_enable(), led_init(), console()
 */
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

	printk("\narmOS initializing...\n");

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

	/* Scheduler */
	// printk("Creating processes...\n");
	// create_processes(5);
	// printk("Done\n");

	/* Console */
	// console(device);

	/* Syscalls */
	int res = copy_process(PF_KTHREAD, (unsigned long) &kernel_process, 0, 0);
	if (res < 0) {
		printk("error while starting kernel process\n");
		return;
	}

	while (1) {
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
