/*
 * aux.h - Definition of AUX registers addresses
 * (Only for Uart)
 * AUX: Auxiliary Peripherals
 */

#ifndef P_AUX_H
#define P_AUX_H

#include <peripherals/gpio.h>

enum
{
	/* The base address for UART */
	/*
	 * AUX_BASE
	 * For raspi 0,1: AUX_BASE = 0x20215000;
	 * For raspi 4:   AUX_BASE = 0xFE215000;
	 */
	AUX_BASE = (GPIO_BASE + 0x15000),

	/* The offsets for reach register for the UART */
	AUX_ENABLES     = (AUX_BASE + 0x04), /* Auxiliary Enables */
	AUX_MU_IO_REG   = (AUX_BASE + 0x40), /* Mini UART I/O Data */
	AUX_MU_IER_REG  = (AUX_BASE + 0x44), /* Mini UART Interrupt Enable */
	AUX_MU_IIR_REG  = (AUX_BASE + 0x48), /* Mini UART Interrupt Identify */
	AUX_MU_LCR_REG  = (AUX_BASE + 0x4C), /* Mini UART Line Control */
	AUX_MU_MCR_REG  = (AUX_BASE + 0x50), /* Mini UART Model Control */
	AUX_MU_LSR_REG  = (AUX_BASE + 0x54), /* Mini UART Line Status */
	AUX_MU_MSR_REG  = (AUX_BASE + 0x58), /* Mini UART Modem Status */
	AUX_MU_SCRATCH  = (AUX_BASE + 0x5C), /* Mini UART Scratch */
	AUX_MU_CNTL_REG = (AUX_BASE + 0x60), /* Mini UART Extra Control */
	AUX_MU_STAT_REG = (AUX_BASE + 0x64), /* Mini UART Extra Status */
	AUX_MU_BAUD_REG = (AUX_BASE + 0x68)  /* Mini UART Baudrate */

};

#endif