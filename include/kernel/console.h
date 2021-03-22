/**
 * \defgroup console console
 * Code for system console.
 * @{
 * @file console.h
 * @brief Definition of functions and types for a minimal console.
 */

#ifndef CONSOLE_H
#define CONSOLE_H

#include <stdint.h>

/**
 * Length of device name, based on running device.
 * @warning It is a temporary solution, based on the supported devices.
 * @see kernel_main()
 */
#define DEVICE_LENGTH 5
/**
 * Length of total prompt string for the console.
 * @warning It is a temporary solution, based on the supported devices.
 * @see console_init()
 */
#define PROMPT_LENGTH 11

/**
 * Available commands for the console.
 */
typedef enum {
	cmd_help,            /**< Prints available commands to the console. */
	cmd_help_led,        /**< Prints available LED commands to the console. */
	cmd_led_pin,         /**< Changes the GPIO Pin for the LED to control. */
	cmd_led_on,          /**< Turns the LED on. */
	cmd_led_off,         /**< Turns the LED off. */
	cmd_led_irq_on,      /**< Pulses the LED with a `msec` milliseconds interval, using System Timer's Interrupt. */
	cmd_led_irq_off,     /**< Stop the System Timer's Interrupt. */
	cmd_led_on_ms,       /**< Turns the LED on for `msec` milliseconds. */
	cmd_led_blink_times, /**< Blinks LED count times for `msec` milliseconds. */
	cmd_led_blink_sos,   /**< Blinks SOS on LED with a `msec` milliseconds interval. */
	cmd_create_procs,    /**< Creates `proc_num` kernel processes. */
	cmd_run_procs,       /**< Runs the created kernel processes concurrently. */
	cmd_kill_procs,      /**< Kills all created kernel processes. */
	cmd_halt             /**< Halts the system. */
} command;

/**
 * Definition of GPIO pin of LED, in order to be accessible from other translation units.
 * @details For example, in order to manipulate the LED with timer interrupts it
 * is used by the handle_timer_1_irq() handler.
 * @see console(), handle_timer_1_irq()
*/
extern uint8_t led_pin_num;

/**
 * Creates the prompt for the minimal console, based on the device.
 * @param device A string pointer for the name of the device.
 * @return A string pointer for the prompt.
 */
char *console_init(char *device);

/**
 * Returns the correct command number, parsed from console input.
 * @param input A string pointer for the input from the console.
 * @return
 * - On success: The command number that matches the input from the @ref command enum.
 * - On failure: -1
 * @see command
 */
int console_get_cmd(char *input);

/**
 * Main console function.
 * @param device A string pointer for the name of the device.
 * @details Executes the commands from console input in an endless loop.
 * @see command, console_init(), console_help(), console_help_led(),
 * uart_gets(), kernel/timer.h, kernel/led.h, kernel/process.h
 */
void console(char *device);

/**
 * Help command
 * @details Prints available commands to the console.
 */
void console_help();

/**
 * Help LED command
 * @details Prints available LED commands to the console.
 */
void console_help_led();

/** @} */

#endif