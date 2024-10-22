/**
 * \ingroup drivers
 * @file led.h
 * @brief Definition of functions for manipulating a LED to a GPIO pin.
 */

#ifndef LED_H
#define LED_H

#include <stdint.h>
#include <stddef.h>

#ifdef AARCH_32
/**
 * \ingroup drivers
 * Raspi Zero W -> GPIO 47 (ACT LED)
 */
#define LED_PIN 47
#elif AARCH_64
/**
 * \ingroup drivers
 * Raspi 3, 4   -> GPIO 17 (LED Connected on physical pin 11)
 * @warning This should change according to the pin you have the LED connected.
 */
#define LED_PIN 17
#endif

/**
 * \ingroup drivers
 * Sets @a pin_num GPIO pin as Output.
 * @param pin_num GPIO pin number.
 * @return
 * - On success: 0
 * - On failure: -1
 *
 * @see gpio_pin_set_func()
 */
int led_init(uint8_t pin_num);

/**
 * \ingroup drivers
 * Turns LED at @a pin_num ON.
 * @param pin_num GPIO pin number.
 * @see gpio_pin_set()
 */
void led_on(uint8_t pin_num);

/**
 * \ingroup drivers
 * Turns LED at @a pin_num OFF.
 * @param pin_num GPIO pin number.
 * @see gpio_pin_clear()
 */
void led_off(uint8_t pin_num);

/**
 * \ingroup drivers
 * Turns LED at @a pin_num ON for @a msec milliseconds.
 * @param pin_num GPIO pin number.
 * @param msec Time to sleep in milliseconds.
 * @see led_on(), led_off(), timer_msleep()
 */
void led_on_ms(uint8_t pin_num, uint32_t msec);

/**
 * \ingroup drivers
 * Makes LED at @a pin_num, to blink once for @a msec milliseconds.
 * @param pin_num GPIO pin number.
 * @param msec Time to sleep in milliseconds.
 * @see led_on(), led_off(), timer_msleep()
 */
void led_pulse(uint8_t pin_num, uint32_t msec);

/**
 * \ingroup drivers
 * Makes LED at @a pin_num, to blink @a count times, for @a msec milliseconds.
 * @param pin_num GPIO pin number.
 * @param count Number of times to blink.
 * @param msec Time to sleep in milliseconds.
 * @see led_pulse()
 * ### Example
 * ```c
 * led_blink_times(LED_PIN, 10, 500);
 * ```
 */
void led_blink_times(uint8_t pin_num, size_t count, uint32_t msec);

/**
 * \ingroup drivers
 * Makes LED at @a pin_num, to blink an SOS message, with an @a msec interval
 * (in milliseconds).
 * @param pin_num GPIO pin number.
 * @param msec Time to sleep in milliseconds.
 * @see led_on(), led_off(), timer_msleep()
 */
void led_blink_sos(uint8_t pin_num, uint32_t msec);

#endif