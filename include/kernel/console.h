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
	cmd_led_on,
	cmd_led_off,
	cmd_halt
} command;

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

#endif