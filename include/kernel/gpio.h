/*
 * gpio.h - Definition of functions for manipulating GPIO registers
 */

#ifndef GPIO_H
#define GPIO_H

#include <stdint.h>

#include <peripherals/gpio.h>

/*
 * Sets the Alternative Function for GPIO pin at pin_num, using GPFSELn
 */
int gpio_pin_set_func(uint8_t pin_num, gpio_func func);

/*
 * Sets the GPIO pin (High) at pin_num, using GPSETn
 */
int gpio_pin_set(uint8_t pin_num);

/*
 * Clears the GPIO pin (Low) at pin_num, using GPCLRn
 */
int gpio_pin_clear(uint8_t pin_num);

#endif