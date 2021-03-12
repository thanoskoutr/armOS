/*
 * led.h - Definition of functions for manipulating a LED to a GPIO pin
 */

#ifndef LED_H
#define LED_H

#include <stddef.h>

/*
 * Sets pin_num GPIO pin as Output
 */
void led_init(uint8_t pin_num);

/*
 * Turns LED at pin_num ON
 */
void led_on(uint8_t pin_num);

/*
 * Turns LED at pin_num OFF
 */
void led_off(uint8_t pin_num);

/*
 * Makes LED at pin_num, to blink once for msec milliseconds
 */
void led_pulse(uint8_t pin_num, uint32_t msec);

/*
 * Makes LED at pin_num, to blink count times, for msec milliseconds
 */
void led_blink_times(uint8_t pin_num, size_t count, uint32_t msec);

/*
 * Makes LED at pin_num, to blink an SOS message, with an msec interval
 * (in milliseconds)
 */
void led_blink_sos(uint8_t pin_num, uint32_t msec);

#endif