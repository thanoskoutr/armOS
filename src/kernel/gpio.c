/*
 * gpio.c - Implementation of functions for manipulating GPIO registers
 */

#include <stdint.h>

#include <kernel/mmio.h>

#include <peripherals/gpio.h>

int gpio_pin_set_func(uint8_t pin_num, gpio_func func)
{
	int func_select_num;
	uint32_t func_select_reg;
	uint32_t selector;
	uint8_t bit_start;

	/* Get n for GPFSELn */
	func_select_num = pin_num / 10;

	/* Find the correct GPFSELn based on n */
	switch (func_select_num) {
	case 0:
		func_select_reg = GPFSEL0;
		break;
	case 1:
		func_select_reg = GPFSEL1;
		break;
	case 2:
		func_select_reg = GPFSEL2;
		break;
	case 3:
		func_select_reg = GPFSEL3;
		break;
	case 4:
		func_select_reg = GPFSEL4;
		break;
	case 5:
		func_select_reg = GPFSEL5;
		break;
	default:
		/* Not a valid GPIO PIN */
		return -1;
	}

	/* Find the starting bit of the pin for the GPFSELn */
	bit_start = (pin_num * 3) % 30;

	selector = mmio_read(func_select_reg);
	selector &= ~(7 << bit_start);		/* Clear GPIO PIN */
	selector |= (func << bit_start);	/* Set Alt Func for GPIO PIN */
	mmio_write(func_select_reg, selector);

	return 0;
}

int gpio_pin_set(uint8_t pin_num)
{
	int num;
	uint32_t set_reg;

	/* Get n for GPSETn */
	num = pin_num / 31;

	switch (num)
	{
	case 0:
		set_reg = GPSET0;
		break;
	case 1:
		set_reg = GPSET1;
		break;
	default:
		/* Not a valid GPIO PIN */
		return -1;
	}

	/* Set GPIO pin */
	mmio_write(set_reg, 1 << pin_num);

	return 0;
}

/*
 * Clears the GPIO pin (Low) at pin_num, using GPCLRn
 */
int gpio_pin_clear(uint8_t pin_num)
{
	int num;
	uint32_t clr_reg;

	/* Get n for GPCLRn */
	num = pin_num / 31;

	switch (num)
	{
	case 0:
		clr_reg = GPCLR0;
		break;
	case 1:
		clr_reg = GPCLR1;
		break;
	default:
		/* Not a valid GPIO PIN */
		return -1;
	}

	/* Clear GPIO pin */
	mmio_write(clr_reg, 1 << pin_num);

	return 0;
}