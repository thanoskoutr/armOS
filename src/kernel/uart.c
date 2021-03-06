/*
 * uart.c - Implementation of basic UART functions
 */

#include <stddef.h>
#include <stdint.h>
#include <kernel/uart.h>

#include "peripherals/gpio.h"
#include "peripherals/aux.h"
#include "peripherals/mbox.h"

/*
 * Memory-Mapped I/O output
 */
void mmio_write(uint32_t reg, uint32_t data)
{
	*(volatile uint32_t*)reg = data;
}

/*
 * Memory-Mapped I/O input
 */
uint32_t mmio_read(uint32_t reg)
{
	return *(volatile uint32_t*)reg;
}

/*
 * Loop <count> times, so the compiler won't optimize away
 */
void delay(int32_t count)
{
	asm volatile("__delay_%=:\n"
			"subs %[count], %[count], #1\n"
			"bne __delay_%=\n"
			: "=r" (count)
			: [count] "0" (count)
			: "cc"
		);
}


/* A Mailbox message with set clock rate of PL011 to 3MHz tag (For raspi 3,4) */
volatile unsigned int __attribute__((aligned(16))) mbox[MBOX_CHANNELS] = {
	9*4, 0, 0x38002, 12, 8, 2, 3000000, 0, 0
};

void uart_init()
{
	uint32_t selector;

	/*
	 * Setup the GPIO pin 14 && 15
	 */
	/* For Raspi ZeroW/3/4? (mini UART) */
	selector = mmio_read(GPFSEL1);
	selector &= ~(7 << 12);		/* Clean GPIO PIN 14 */
	selector |= 2 << 12;		/* Set Alt 5 for GPIO PIN 14 */
	selector &= ~(7 << 15);		/* Clean GPIO PIN 15 */
	selector |= 2 << 15;		/* Set Alt 5 for GPIO PIN 15 */
	mmio_write(GPFSEL1, selector);

	/* Disable pull up/down for all GPIO pins & delay for 150 cycles */
	mmio_write(GPPUD, 0x00000000);
	delay(150);

	/* Disable pull up/down for pin 14 (TXD), 15 (RXD) & delay for 150 cycles */
	mmio_write(GPPUDCLK0, (1 << 14) | (1 << 15));
	delay(150);

	/* Write 0 to GPPUDCLK0 to make it take effect */
	mmio_write(GPPUDCLK0, 0x00000000);



#if defined(MODEL_3) || defined(MODEL_4)
	/*
	* For Raspi3 and 4 the UART_CLOCK is system-clock dependent by default
	* Set it to 3Mhz so that we can consistently set the baud rate
	*/

	/* UART_CLOCK = 30000000; */
	unsigned int r = (((unsigned int)(&mbox) & ~0xF) | 8);
	/* Wait until we can talk to the VC */
	while ( mmio_read(MBOX_STATUS) & 0x80000000 ) { }
	/* Send our msg to property channel and wait for the response */
	mmio_write(MBOX_WRITE, r);
	while ( (mmio_read(MBOX_STATUS) & 0x40000000) ||
					mmio_read(MBOX_READ) != r ) { }
#endif

	/* Enable mini UART*/
	mmio_write(AUX_ENABLES, 1);
	/* Disable auto flow control and disable receiver and transmitter */
	mmio_write(AUX_MU_CNTL_REG, 0);
	/* Disable receive and transmit interrupts */
	mmio_write(AUX_MU_IER_REG, 0);

	/* Not possible read for Interrupt ID, FIFO enables */
	// mmio_write(AUX_MU_IIR_REG, 0xC6);

	/* Enable 8 bit mode */
	mmio_write(AUX_MU_LCR_REG, 3);
	/* Set RTS line to be always high */
	mmio_write(AUX_MU_MCR_REG, 0);

	/* Set baud rate to 115200 */
	/* (( System_Clock_Freq / baudrate_reg) / 8 ) - 1 */
	/* ((250,000,000 / 115200) / 8) - 1 = 270 */
	mmio_write(AUX_MU_BAUD_REG, 270);

	/* Finally, enable transmitter and receiver */
	mmio_write(AUX_MU_CNTL_REG, 3);

}

void uart_putc(unsigned char c)
{
	/* Wait for UART to become ready to transmit */
	while (1) {
		if (mmio_read(AUX_MU_LSR_REG) & (1 << 5))
			break;
	}
	mmio_write(AUX_MU_IO_REG, c);
	/*
	 * AUX_MU_LSR_REG shows the data status.
	 * If bit 5 is set the transmit FIFO can accept at least 1 byte.
	 */
}


unsigned char uart_getc()
{
	/* Wait for UART to have received something */
	while (1) {
		if (mmio_read(AUX_MU_LSR_REG) & (1 << 0))
			break;
	}
	return mmio_read(AUX_MU_IO_REG);
	/*
	 * AUX_MU_LSR_REG shows the data status.
	 * If bit 0 is set the receive FIFO holds at least 1 symbol.
	 */
}

void uart_puts(const char* str)
{
	for (size_t i = 0; str[i] != '\0'; i++)
		uart_putc((unsigned char)str[i]);
}
