/*
 * console.c - Implementation of a minimal console
 */

#include <stdint.h>

#include <kernel/console.h>
#include <kernel/printk.h>
#include <kernel/uart.h>
#include <kernel/led.h>
#include <kernel/timer.h>
#include <kernel/scheduler.h>
#include <kernel/process.h>

#include <common/string.h>
#include <common/stdlib.h>

/* Initialize default LED pin per device */
uint8_t led_pin_num = LED_PIN;

char *console_init(char *device)
{
	static char prompt[PROMPT_LENGTH];

	/* Create prompt */
	strcpy(prompt, "root@");
	strcat(prompt, device);
	strcat(prompt, "#");

	return prompt;
}

int console_get_cmd(char *input)
{
	if (strcmp(input, "help") == 0)
		return cmd_help;
	else if (strcmp(input, "help_led") == 0)
		return cmd_help_led;
	else if (strcmp(input, "led_pin") == 0)
		return cmd_led_pin;
	else if (strcmp(input, "led_on") == 0)
		return cmd_led_on;
	else if (strcmp(input, "led_off") == 0)
		return cmd_led_off;
	else if (strcmp(input, "led_irq_on") == 0)
		return cmd_led_irq_on;
	else if (strcmp(input, "led_irq_off") == 0)
		return cmd_led_irq_off;
	else if (strcmp(input, "led_on_ms") == 0)
		return cmd_led_on_ms;
	else if (strcmp(input, "led_blink_times") == 0)
		return cmd_led_blink_times;
	else if (strcmp(input, "led_blink_sos") == 0)
		return cmd_led_blink_sos;
	else if (strcmp(input, "create_procs") == 0)
		return cmd_create_procs;
	else if (strcmp(input, "run_procs") == 0)
		return cmd_run_procs;
	else if (strcmp(input, "kill_procs") == 0)
		return cmd_kill_procs;
	else if (strcmp(input, "halt") == 0)
		return cmd_halt;
	else
		return -1;
}

void console(char *device)
{
	char *input;
	char *args;
	char *prompt;
	int msec, count, pin_num, proc_num;

	/* Get prompt */
	prompt = console_init(device);

	/* Print console info */
	printk("\n");
	printk("This is a minimal console, type 'help' to see the available commands. (Maximum Input Length: %d)\n", MAX_INPUT_LENGTH);

	/* Main functionality */
	while (1) {
		/* Print prompt */
		printk("%s ", prompt);
		/* Read from serial */
		input = uart_gets();
		printk("\n");
		printk("--DEBUG-- input: %s\n", input);

		/* Find given command */
		command cmd = console_get_cmd(input);

		switch (cmd) {
		case cmd_help:
			console_help();
			break;
		case cmd_help_led:
			console_help_led();
			break;
		case cmd_led_pin:
			printk("Enter GPIO Pin: ");
			args = uart_gets();
			printk("\n");
			pin_num = atoi(args);
			if (pin_num <= 0) {
				printk("Not valid Pin: %s\n", args);
				break;
			}
			if (led_init(pin_num) < 0) {
				printk("Error: Not a valid GPIO PIN\n");
				break;
			}
			printk("Changed LED Pin to %d.\n", pin_num);
			led_pin_num = pin_num;
			break;
		case cmd_led_on:
			printk("Turning LED on.\n");
			led_on(led_pin_num);
			break;
		case cmd_led_off:
			printk("Turning LED off.\n");
			led_off(led_pin_num);
			break;
		case cmd_led_irq_on:
			printk("Enter milliseconds: ");
			args = uart_gets();
			printk("\n");
			msec = atoi(args);
			if (msec <= 0) {
				printk("Not valid ms: %s\n", args);
				break;
			}
			else if (msec <= LED_MSEC_IRQ) {
				printk("Must be > %dms\n", LED_MSEC_IRQ);
				break;
			}
			printk("Started System Timer Interrupt every %dms.\n", msec);
			timer_1_init((uint32_t) msec);
			break;
		case cmd_led_irq_off:
			printk("Stopped System Timer Interrupt.\n");
			timer_1_stop();
			break;
		case cmd_led_on_ms:
			printk("Enter milliseconds: ");
			args = uart_gets();
			printk("\n");
			msec = atoi(args);
			if (msec <= 0) {
				printk("Not valid ms: %s\n", args);
				break;
			}
			printk("Turning LED on for %dms\n", msec);
			led_on_ms(led_pin_num, (uint32_t) msec);
			break;

		case cmd_led_blink_times:
			printk("Enter milliseconds: ");
			args = uart_gets();
			printk("\n");
			msec = atoi(args);
			if (msec <= 0) {
				printk("Not valid ms: %s\n", args);
				break;
			}
			printk("Enter times to blink: ");
			args = uart_gets();
			printk("\n");
			count = atoi(args);
			if (count <= 0) {
				printk("Not a valid number: %s\n", args);
				break;
			}
			printk("Blink LED %d times with a %dms pulse.\n", count, msec);
			led_blink_times(led_pin_num, (size_t) count, (uint32_t) msec);
			break;
		case cmd_led_blink_sos:
			printk("Enter milliseconds: ");
			args = uart_gets();
			printk("\n");
			msec = atoi(args);
			if (msec <= 0) {
				printk("Not valid ms: %s\n", args);
				break;
			}
			printk("Blink SOS on LED, with a %dms time interval.\n", msec);
			led_blink_sos(led_pin_num, (uint32_t) msec);
			break;
		case cmd_create_procs:
			printk("Enter number of process(es): ");
			args = uart_gets();
			printk("\n");
			proc_num = atoi(args);
			if (proc_num <= 0 || proc_num >= NR_TASKS) {
				printk("Not a valid number: %s\n", args);
				printk("Total processes must be: 0 < procs < %d \n", NR_TASKS);
				break;
			}
			printk("Creating %d process(es)...\n", proc_num);
			create_processes(proc_num);
			printk("Done\n");
			break;
		case cmd_run_procs:
			/* Initialize Timer 3 for scheduler */
			printk("Initializing Timer 3...");
			timer_3_init(2000);
			printk("Done\n");
			/* Schedule */
			printk("Entering in scheduling mode...\n");
			while(1) {
				/*
				* Core scheduler function.
				* Checks whether there is a new task,
				* that needs to preempt the current one.
				*/
				schedule();
				/* Continue or Stop, based on user input */
				timer_3_stop();
				printk("Continue? [y/n]: ");
				args = uart_gets();
				printk("\n");
				if (strcmp(args, "n") == 0)
					break;
				else {
					timer_3_init(2000);
					continue;
				}
			}
			/* Stop Timer 3 from calling the scheduler */
			timer_3_stop();
			break;
		case cmd_kill_procs:
			printk("Killing all process(es)...\n");
			kill_processes();
			printk("Done\n");
			break;
		case cmd_halt:
			printk("Halt.\n");
			printk("So long and thanks for all the fish...\n");
			return;
		default:
			printk("%s: command not found\n", input);
			printk("type 'help' to see the available commands\n");
			break;
		}
	}

}

void console_help()
{
	printk("Available commands:\n");
	printk("    help:\n");
	printk("        Prints available commands to the console.\n");
	printk("    help_led:\n");
	printk("        Prints available LED commands to the console.\n");
	printk("    create_procs:\n");
	printk("        Creates proc_num kernel processes.\n");
	printk("    run_procs:\n");
	printk("        Runs the created kernel processes concurrently.\n");
	printk("    kill_procs:\n");
	printk("        Kills all created kernel processes.\n");
	printk("    halt:\n");
	printk("        Halts the system.\n");
}

void console_help_led()
{
	printk("Available LED commands:\n");
	printk("    led_pin:\n");
	printk("        Changes the GPIO Pin for the LED to control.\n");
	printk("    led_on:\n");
	printk("        Turns the LED on.\n");
	printk("    led_off:\n");
	printk("        Turns the LED off.\n");
	printk("    led_irq_on:\n");
	printk("        Pulses the LED with a msec milliseconds interval, using System Timer's Interrupt.\n");
	printk("    led_irq_off:\n");
	printk("        Stop the System Timer's Interrupt.\n");
	printk("    led_on_ms:\n");
	printk("        Turns the LED on for msec milliseconds.\n");
	printk("    led_blink_times:\n");
	printk("        Blinks LED count times for msec milliseconds.\n");
	printk("    led_blink_sos:\n");
	printk("        Blinks SOS on LED with a msec milliseconds interval.\n");
}