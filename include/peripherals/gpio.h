/**
 * @file gpio.h
 * @brief Definition of GPIO registers addresses.
 * @details GPIO : General Purpose IO
 */

#ifndef P_GPIO_H
#define P_GPIO_H

#include <peripherals/base.h>

/**
 * GPIO Pins available functionalities: 5 Alternative Functions, Input, Output.
 */
typedef enum _gpio_func {
	GF_INPUT  = 0, /**< Input */
	GF_OUTPUT = 1, /**< Output */
	GF_ALT_0  = 4, /**< Alternative Function 0 */
	GF_ALT_1  = 5, /**< Alternative Function 1 */
	GF_ALT_2  = 6, /**< Alternative Function 2 */
	GF_ALT_3  = 7, /**< Alternative Function 3 */
	GF_ALT_4  = 3, /**< Alternative Function 4 */
	GF_ALT_5  = 2, /**< Alternative Function 5 */
} gpio_func;

/**
 * GPIO registers addresses.
 */
enum
{
	/**
	 * The base address for GPIO.             \n
	 * For raspi 0,1: GPIO_BASE = 0x20200000; \n
	 * For raspi 4:   GPIO_BASE = 0xFE200000;
	 */
	GPIO_BASE = (MMIO_BASE + 0x200000),

	/**
	 * GPIO Function Select 0,1,2,3,4,5 \n
	 * GPFSELn register are used to control alternative functions for pins: \n
	 */
	GPFSEL0 = (GPIO_BASE + 0x00), /**< GPFSEL0: pins 0-9 */
	GPFSEL1 = (GPIO_BASE + 0x04), /**< GPFSEL1: pins 10-19 */
	GPFSEL2 = (GPIO_BASE + 0x08), /**< GPFSEL2: pins 20-29 */
	GPFSEL3 = (GPIO_BASE + 0x0C), /**< GPFSEL3: pins 30-39 */
	GPFSEL4 = (GPIO_BASE + 0x10), /**< GPFSEL4: pins 40-49 */
	GPFSEL5 = (GPIO_BASE + 0x14), /**< GPFSEL5: pins 50-53 or 50-57 */

	/**
	 * GPIO Pin Output Set 0,1 \n
	 */
	GPSET0 = (GPIO_BASE + 0x1C), /**< The GPSET0 register is used to set GPIO pins 0-31 */
	GPSET1 = (GPIO_BASE + 0x20), /**< The GPSET1 register is used to set GPIO pins 32-53 */

	/**
	 * GPIO Pin Output Clear 0,1 \n
	 */
	GPCLR0 = (GPIO_BASE + 0x28), /**< The GPCLR0 register is used to clear GPIO pins 0-31 */
	GPCLR1 = (GPIO_BASE + 0x2C), /**< The GPCLR1 register is used to clear GPIO pins 32-53 */

	GPLEV0 = (GPIO_BASE + 0x34), /**< GPIO Pin Level 0 */
	GPLEV1 = (GPIO_BASE + 0x38), /**< GPIO Pin Level 1 */
	GPEDS0 = (GPIO_BASE + 0x40), /**< GPIO Pin Event Detect Status 0 */
	GPEDS1 = (GPIO_BASE + 0x44), /**< GPIO Pin Event Detect Status 1 */
	GPREN0 = (GPIO_BASE + 0x4C), /**< GPIO Pin Rising Edge Detect Enable 0 */
	GPREN1 = (GPIO_BASE + 0x50), /**< GPIO Pin Rising Edge Detect Enable 1 */
	GPFEN0 = (GPIO_BASE + 0x58), /**< GPIO Pin Falling Edge Detect Enable 0 */
	GPFEN1 = (GPIO_BASE + 0x5C), /**< GPIO Pin Falling Edge Detect Enable 1 */
	GPHEN0 = (GPIO_BASE + 0x64), /**< GPIO Pin High Detect Enable 0 */
	GPHEN1 = (GPIO_BASE + 0x68), /**< GPIO Pin High Detect Enable 1 */
	GPLEN0 = (GPIO_BASE + 0x70), /**< GPIO Pin Low Detect Enable 0 */
	GPLEN1 = (GPIO_BASE + 0x74), /**< GPIO Pin Low Detect Enable 1 */
	GPAREN0 = (GPIO_BASE + 0x7C), /**< GPIO Pin Async. Rising Edge Detect 0 */
	GPAREN1 = (GPIO_BASE + 0x80), /**< GPIO Pin Async. Rising Edge Detect 1 */
	GPAFEN0 = (GPIO_BASE + 0x88), /**< GPIO Pin Async. Falling Edge Detect 0 */
	GPAFEN1 = (GPIO_BASE + 0x8C), /**< GPIO Pin Async. Falling Edge Detect 1 */

#if defined(MODEL_0) || defined(MODEL_2) || defined(MODEL_3)
	/* Broadcom 2835, 2836, 2837 specific GPIO registers */
	/**
	 * GPIO Pin Pull-up/down Enable
	 * Controls actuation of pull up/down to ALL GPIO pins
	 */
	GPPUD = (GPIO_BASE + 0x94),
	/*
	 * GPIO Pin Pull-up/down Enable Clocks 0,1
	 * Controls actuation of pull up/down for specific GPIO pins
	 */
	GPPUDCLK0 = (GPIO_BASE + 0x98), /**< GPIO Pin Pull-up/down Enable Clocks 0 */
	GPPUDCLK1 = (GPIO_BASE + 0x9C)  /**< GPIO Pin Pull-up/down Enable Clocks 1 */

#elif defined(MODEL_4)
	/* Broadcom 2711 specific GPIO registers */
	/*
	 * GPIO Pull-up / Pull-down Registers 0,1,2,3
	 * Controls the actuation of the internal pull-up/down resistors.
	 * Reading these registers gives the current pull-state.
	 */
	GPIO_PUP_PDN_CNTRL_REG0 = (GPIO_BASE + 0xE4), /**< GPIO Pull-up / Pull-down Registers 0 */
	GPIO_PUP_PDN_CNTRL_REG1 = (GPIO_BASE + 0xE8), /**< GPIO Pull-up / Pull-down Registers 1 */
	GPIO_PUP_PDN_CNTRL_REG2 = (GPIO_BASE + 0xEC), /**< GPIO Pull-up / Pull-down Registers 2 */
	GPIO_PUP_PDN_CNTRL_REG3 = (GPIO_BASE + 0xF0)  /**< GPIO Pull-up / Pull-down Registers 3 */
#endif
};

#endif