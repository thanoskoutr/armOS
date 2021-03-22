/**
 * \ingroup drivers
 * @file gpio.h
 * @brief Definition of functions for manipulating GPIO registers.
 */

#ifndef GPIO_H
#define GPIO_H

#include <stdint.h>

#include <peripherals/gpio.h>

/**
 * \ingroup drivers
 * Sets the Alternative Function @a func for GPIO pin at @a pin_num, using GPFSELn
 * ( @ref GPFSEL0 - @ref GPFSEL5).
 * @param pin_num GPIO pin number.
 * @param func Alternative Function.
 * @return
 * - On success: 0
 * - On failure: -1
 * @see gpio_func, peripherals/gpio.h
 */
int gpio_pin_set_func(uint8_t pin_num, gpio_func func);

/**
 * \ingroup drivers
 * Sets the GPIO pin (High) at @a pin_num, using GPSETn ( @ref GPSET0, @ref GPSET1).
 * @param pin_num GPIO pin number.
 * @return
 * - On success: 0
 * - On failure: -1
 *
 * @see peripherals/gpio.h
 */
int gpio_pin_set(uint8_t pin_num);

/**
 * \ingroup drivers
 * Clears the GPIO pin (Low) at @a pin_num, using GPCLRn ( @ref GPCLR0, @ref GPCLR1).
 * @param pin_num GPIO pin number.
 * @return
 * - On success: 0
 * - On failure: -1
 *
 * @see peripherals/gpio.h
 */
int gpio_pin_clear(uint8_t pin_num);

#endif