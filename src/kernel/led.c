/*
 * led.c - Implementation of functions for manipulating a LED to a GPIO pin
 */

#include <stdint.h>
#include <stddef.h>

#include <kernel/mmio.h>
#include <kernel/gpio.h>
#include <kernel/printk.h>
#include <kernel/timer.h>

#include <peripherals/gpio.h>


void led_init(uint8_t pin_num)
{
	int res;

	/* Initializes the pin as Output */
	res = gpio_pin_set_func(pin_num, GF_OUTPUT);

	/* Print error message, for not valid pin */
	if (res < 0) {
		printk("Error: Not a valid GPIO PIN\n");
	}
}

void led_on(uint8_t pin_num)
{
	int res;

	/* Set LEDs output (Turn ON) */
#ifdef MODEL_0
	/*
	 * Check if it is the ACT LED,
	 * Inverted logic on ACT LED of Pi Zero / Zero W
	 */
	if (pin_num == 47)
		res = gpio_pin_clear(pin_num);
	else
		res = gpio_pin_set(pin_num);
#else
	res = gpio_pin_set(pin_num);
#endif

	/* Print error message, for not valid pin */
	if (res < 0) {
		printk("Error: Not a valid GPIO PIN\n");
	}
}

void led_off(uint8_t pin_num)
{
	int res;

	/* Clear LEDs output (Turn OFF) */
#ifdef MODEL_0
	/*
	 * Check if it is the ACT LED,
	 * Inverted logic on ACT LED of Pi Zero / Zero W
	 */
	if (pin_num == 47)
		res = gpio_pin_set(pin_num);
	else
		res = gpio_pin_clear(pin_num);
#else
	res = gpio_pin_clear(pin_num);
#endif

	/* Print error message, for not valid pin */
	if (res < 0) {
		printk("Error: Not a valid GPIO PIN\n");
	}
}

void led_on_ms(uint8_t pin_num, uint32_t msec)
{
	/* Set LEDs output (Turn ON) */
	led_on(pin_num);

	/* Sleep for msec milliseconds */
	timer_msleep(msec);

	/* Clear LEDs output (Turn OFF) */
	led_off(pin_num);
}

void led_pulse(uint8_t pin_num, uint32_t msec)
{
	/* Set LEDs output (Turn ON) */
	led_on(pin_num);

	/* Sleep for msec milliseconds */
	timer_msleep(msec);

	/* Clear LEDs output (Turn OFF) */
	led_off(pin_num);

	/* Sleep for msec milliseconds */
	timer_msleep(msec);
}


void led_blink_times(uint8_t pin_num, size_t count, uint32_t msec)
{
	for (size_t i = 0; i < count; i++) {
		led_pulse(pin_num, msec);
	}
}


void led_blink_sos(uint8_t pin_num, uint32_t msec)
{
	uint32_t dot_msec, dash_msec;
	uint32_t symbol_space, letter_space;

	dot_msec = msec;
	dash_msec = 3 * msec;
	symbol_space = msec;
	letter_space = 3 * msec;

	/* S = ... */
	for (size_t i = 0; i < 2; i++) {
		led_on(pin_num);
		timer_msleep(dot_msec);
		led_off(pin_num);
		timer_msleep(symbol_space);
	}
	led_on(pin_num);
	timer_msleep(dot_msec);
	led_off(pin_num);
	timer_msleep(letter_space);

	/* O = --- */
	for (size_t i = 0; i < 2; i++) {
		led_on(pin_num);
		timer_msleep(dash_msec);
		led_off(pin_num);
		timer_msleep(symbol_space);
	}
	led_on(pin_num);
	timer_msleep(dash_msec);
	led_off(pin_num);
	timer_msleep(letter_space);

	/* S = ... */
	for (size_t i = 0; i < 3; i++) {
		led_on(pin_num);
		timer_msleep(dot_msec);
		led_off(pin_num);
		timer_msleep(symbol_space);
	}
}

