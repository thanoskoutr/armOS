/*
 * console.h - Definitions for a minimal console
 */

#ifndef CONSOLE_H
#define CONSOLE_H


#define DEVICE_LENGTH 5
#define PROMPT_LENGTH 11

/*
 * Available commands
 */
typedef enum _command {
	cmd_help,
	cmd_help_led,
	cmd_led_pin,
	cmd_led_on,
	cmd_led_off,
	cmd_led_irq_on,
	cmd_led_irq_off,
	cmd_led_on_ms,
	cmd_led_blink_times,
	cmd_led_blink_sos,
	cmd_create_procs,
	cmd_run_procs,
	cmd_kill_procs,
	cmd_halt
} command;

extern uint8_t led_pin_num;

/*
 * Creates the prompt for the minimal console, based on the device
 */
char *console_init(char *device);

/*
 * Returns the correct command number, parsed from console input
 */
int console_get_cmd(char *input);

/*
 * Main console function.
 * Executes the commands from console input in an endless loop
 */
void console(char *device);

/*
 * Command: help
 * Prints available commands to the console
 */
void console_help();

/*
 * Command: help_led
 * Prints available LED commands to the console
 */
void console_help_led();


#endif