/*
 * gpio.h - Definition of GPIO registers addresses
 * GPIO: General Purpose IO
 */

#ifndef P_GPIO_H
#define P_GPIO_H

#include <peripherals/base.h>

enum
{
	/* The offsets for reach register */
	/*
	 * GPIO_BASE
	 * For raspi 0,1: GPIO_BASE = 0x20200000;
	 * For raspi 4:   GPIO_BASE = 0xFE200000;
	 */
	GPIO_BASE = (MMIO_BASE + 0x200000),

	/*
	 * GPIO Function Select 1
	 * The GPFSEL1 register is used to control alternative functions
	 * for pins 10-19
	 */
	GPFSEL1 = (GPIO_BASE + 0x04),

#if defined(MODEL_0) || defined(MODEL_2) || defined(MODEL_3)
	/* Broadcom 2835, 2836, 2837 specific GPIO registers */
	/*
	 * GPIO Pin Pull-up/down Enable
	 * Controls actuation of pull up/down to ALL GPIO pins
	 */
	GPPUD = (GPIO_BASE + 0x94),
	/*
	 * GPIO Pin Pull-up/down Enable Clock 0
	 * Controls actuation of pull up/down for specific GPIO pin
	 */
	GPPUDCLK0 = (GPIO_BASE + 0x98)

#elif defined(MODEL_4)
	/* Broadcom 2711 specific GPIO registers */
	/* GPIO Pull-up / Pull-down Register 0
	 * Controls the actuation of the internal pull-up/down resistors.
	 * Reading these registers gives the current pull-state.
	 */
	GPIO_PUP_PDN_CNTRL_REG0 = (GPIO_BASE + 0xE4)
#endif
};

#endif