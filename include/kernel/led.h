/*
 * led.h - Definition of functions for manipulating a LED to a GPIO pin
 */

#ifndef LED_H
#define LED_H

#include <stdint.h>
#include <stddef.h>

/*
 * Raspi Zero W -> GPIO 47 (ACT LED)
 * Raspi 3, 4   -> GPIO 17 (LED Connected on physical pin 11)
 */
#ifdef AARCH_32
#define LED_PIN 47
#elif AARCH_64
#define LED_PIN 17
#endif

/*
 * Sets pin_num GPIO pin as Output
 */
int led_init(uint8_t pin_num);

/*
 * Turns LED at pin_num ON
 */
void led_on(uint8_t pin_num);

/*
 * Turns LED at pin_num OFF
 */
void led_off(uint8_t pin_num);

/*
 * Turns LED at pin_num ON for msec milliseconds
 */
void led_on_ms(uint8_t pin_num, uint32_t msec);

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