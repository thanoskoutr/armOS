/*
 * console.c - Implementation of a minimal console
 */

#include <stdint.h>

#include <kernel/console.h>
#include <kernel/printk.h>
#include <kernel/uart.h>
#include <kernel/led.h>

#include <common/string.h>
#include <common/stdlib.h>

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
	else if (strcmp(input, "led_on") == 0)
		return cmd_led_on;
	else if (strcmp(input, "led_off") == 0)
		return cmd_led_off;
	else if (strcmp(input, "led_on_ms") == 0)
		return cmd_led_on_ms;
	else if (strcmp(input, "led_blink_times") == 0)
		return cmd_led_blink_times;
	else if (strcmp(input, "led_blink_sos") == 0)
		return cmd_led_blink_sos;
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
	int msec;

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
		case cmd_led_on:
			printk("Turning LED on.\n");
			led_on(LED_PIN);
			break;
		case cmd_led_off:
			printk("Turning LED off.\n");
			led_off(LED_PIN);
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
			led_on_ms(LED_PIN, (uint32_t) msec);
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
			printk("Blink LED 10 times with a %dms pulse.\n", msec);
			led_blink_times(LED_PIN, 10, (uint32_t) msec);
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
			led_blink_sos(LED_PIN, (uint32_t) msec);
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
	printk("    led_on:\n");
	printk("        Turns the LED on.\n");
	printk("    led_off:\n");
	printk("        Turns the LED on.\n");
	printk("    led_on_ms:\n");
	printk("        Turns the LED on for msec milliseconds.\n");
	printk("    led_blink_times:\n");
	printk("        Blinks LED count times for msec milliseconds.\n");
	printk("    led_blink_sos:\n");
	printk("        Blinks SOS on LED with a msec milliseconds interval.\n");
	printk("    halt:\n");
	printk("        Halts the system.\n");

}