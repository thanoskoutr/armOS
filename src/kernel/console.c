/*
 * console.c - Implementation of a minimal console
 */

#include <kernel/console.h>
#include <kernel/printk.h>
#include <kernel/uart.h>

#include <common/string.h>

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
	else if (strcmp(input, "halt") == 0)
		return cmd_halt;
	else
		return -1;
}

void console(char *device)
{
	char *input;
	char *prompt;

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
		printk("input: %s\n", input);

		printk("prompt adr: %d\n", prompt);
		printk("input  adr: %d\n", input);


		/* Find given command */
		command cmd = console_get_cmd(input);

		switch (cmd) {
		case cmd_help:
			printk("HELP\n");
			break;
		case cmd_led_on:
			printk("LED_ON\n");
			break;
		case cmd_led_off:
			printk("LED_OFF\n");
			break;
		case cmd_halt:
			printk("HALT\n");
			break;
		default:
			printk("%s: command not found\n", input);
			break;
		}
	}

}