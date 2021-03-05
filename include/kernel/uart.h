/*
 * uart.h - Definition of basic UART functions
 * Definition of base MMIO, GPIO, AUX addresses
 * MMIO: Memory Mapped IO
 * GPIO: General Purpose IO
 * AUX: Auxiliary Peripherals
 */

#include <stddef.h>
#include <stdint.h>

#ifndef UART_H
#define UART_H

#define MBOX_CHANNELS 9

void mmio_write(uint32_t reg, uint32_t data);

uint32_t mmio_read(uint32_t reg);

void delay(int32_t count);

enum
{
	/* The MMIO area base address */
	/*
	 * For raspi 0,1: MMIO_BASE = 0x20000000;
	 * For raspi 2,3: MMIO_BASE = 0x3F000000;
	 * For raspi 4:   MMIO_BASE = 0xFE000000;
	 */

#ifdef MODEL_0
	MMIO_BASE = 0x20000000,
#elif MODEL_2
	MMIO_BASE = 0x3F000000,
#elif MODEL_3
	MMIO_BASE = 0x3F000000,
#elif MODEL_4
	MMIO_BASE = 0xFE000000,
#endif

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
	GPPUDCLK0 = (GPIO_BASE + 0x98),


	/* The base address for UART */
	/*
	 * AUX_BASE
	 * For raspi 0,1: AUX_BASE = 0x20215000;
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
	AUX_MU_BAUD_REG = (AUX_BASE + 0x68), /* Mini UART Baudrate */

	/* The offsets for Mailbox registers (For raspi 3,4) */
	MBOX_BASE    = (MMIO_BASE + 0xB880),
	MBOX_READ    = (MBOX_BASE + 0x00),
	MBOX_STATUS  = (MBOX_BASE + 0x18),
	MBOX_WRITE   = (MBOX_BASE + 0x20)
};

extern volatile unsigned int __attribute__((aligned(16))) mbox[MBOX_CHANNELS];

void uart_init();

void uart_putc(unsigned char c);

unsigned char uart_getc();

void uart_puts(const char* str);


#endif