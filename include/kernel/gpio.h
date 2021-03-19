/**
 * @file gpio.h
 * @brief Definition of functions for manipulating GPIO registers.
 */

#ifndef GPIO_H
#define GPIO_H

#include <stdint.h>

#include <peripherals/gpio.h>

/**
 * Sets the Alternative Function @a func for GPIO pin at @a pin_num, using GPFSELn.
 * @param pin_num GPIO pin number.
 * @param func Alternative Function.
 * @return
 * - On success: 0
 * - On failure: -1
 */
int gpio_pin_set_func(uint8_t pin_num, gpio_func func);

/**
 * Sets the GPIO pin (High) at @a pin_num, using GPSETn.
 * @param pin_num GPIO pin number.
 * @return
 * - On success: 0
 * - On failure: -1
 */
int gpio_pin_set(uint8_t pin_num);

/**
 * Clears the GPIO pin (Low) at @a pin_num, using GPCLRn.
 * @param pin_num GPIO pin number.
 * @return
 * - On success: 0
 * - On failure: -1
 */
int gpio_pin_clear(uint8_t pin_num);

#endif