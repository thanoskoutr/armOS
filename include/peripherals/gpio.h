/*
 * gpio.h - Definition of GPIO registers addresses
 * GPIO: General Purpose IO
 */

#ifndef P_GPIO_H
#define P_GPIO_H

#include "peripherals/base.h"

enum
{
	/* The offsets for reach register */
	/*
	 * GPIO_BASE
	 * For raspi 0,1: GPIO_BASE = 0x20200000;
	 */
	GPIO_BASE = (MMIO_BASE + 0x200000),

	/*
	 * GPIO Function Select 1
	 * The GPFSEL1 register is used to control alternative functions
	 * for pins 10-19
	 */
	GPFSEL1 = (GPIO_BASE + 0x04),
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
};

#endif