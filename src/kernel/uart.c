/**
 * \ingroup drivers
 * @file uart.c
 * @brief Implementation of basic UART functions
 */

#include <stddef.h>
#include <stdint.h>

#include <common/string.h>

#include <kernel/uart.h>
#include <kernel/mmio.h>

#include <peripherals/gpio.h>
#include <peripherals/aux.h>


void uart_init()
{
	uint32_t selector;

	/*
	 * Setup the GPIO pin 14 && 15
	 */

	/* Set Alternative Function 5 for GPIO pins 14, 15
	 * Enables mini UART for boards that use it as a primary UART
	 * Boards: Raspi Zero W, Raspi 3, Raspi 4
	 */
	selector = mmio_read(GPFSEL1);
	selector &= ~(7 << 12);		/* Clear GPIO PIN 14 */
	selector |= 2 << 12;		/* Set Alt 5 for GPIO PIN 14 */
	selector &= ~(7 << 15);		/* Clear GPIO PIN 15 */
	selector |= 2 << 15;		/* Set Alt 5 for GPIO PIN 15 */
	mmio_write(GPFSEL1, selector);

	/*
	 * Disable pull up/down for pin 14 && 15
	 */
#if defined(MODEL_0) || defined(MODEL_2) || defined(MODEL_3)
	/* Disable pull up/down for all GPIO pins & delay for 150 cycles */
	mmio_write(GPPUD, 0x00000000);
	delay(150);

	/* Disable pull up/down for pin 14 (TXD), 15 (RXD) & delay for 150 cycles */
	mmio_write(GPPUDCLK0, (1 << 14) | (1 << 15));
	delay(150);

	/* Write 0 to GPPUDCLK0 to make it take effect */
	mmio_write(GPPUDCLK0, 0x00000000);

#elif defined(MODEL_4)
	/* Disable pull up/down for pin 14 (TXD), 15 (RXD) */
	selector = mmio_read(GPIO_PUP_PDN_CNTRL_REG0);
	/* 31:30 bits - Resistor Select for GPIO15 */
	/* 29:28 bits - Resistor Select for GPIO14 */
	/* Clear GPIO15, GPIO14 Resistor Select pins -> Disables pull up/down */
	selector &= ~((1 << 31) | (1 << 30) | (1 << 29) | (1 << 28));
	mmio_write(GPIO_PUP_PDN_CNTRL_REG0, selector);
#endif

	/* Enable mini UART*/
	mmio_write(AUX_ENABLES, 1);
	/* Disable auto flow control and disable receiver and transmitter */
	mmio_write(AUX_MU_CNTL_REG, 0);

	/* Disable receive and transmit interrupts */
	// mmio_write(AUX_MU_IER_REG, 0);

	/*
	 * Bit 0: Enable receive interrupt
	 * Bit 1: Enable transmit interrupt
	 * Bit 2&3: Required in order to receive interrupts
	 */
	mmio_write(AUX_MU_IER_REG, (1 << 0) | (1 << 2) | (1 << 3));

	/* Clear the receive and transmit FIFO, and enables FIFO */
	mmio_write(AUX_MU_IIR_REG, 0xC6);

	/* Enable 8 bit mode */
	mmio_write(AUX_MU_LCR_REG, 3);
	/* Set RTS line to be always high */
	mmio_write(AUX_MU_MCR_REG, 0);

	/* Set baud rate to 115200 */
#if defined(MODEL_0) || defined(MODEL_2) || defined(MODEL_3)
	/* System_Clock_Freq = 250 MHz */
	/* (( System_Clock_Freq / baudrate_reg) / 8 ) - 1 */
	/* ((250,000,000 / 115200) / 8) - 1 = 270 */
	mmio_write(AUX_MU_BAUD_REG, 270);
#elif defined(MODEL_4)
	/* System_Clock_Freq = 500 MHz */
	/* (( System_Clock_Freq / baudrate_reg) / 8 ) - 1 */
	/* ((500,000,000 / 115200) / 8) - 1 = 541 */
	mmio_write(AUX_MU_BAUD_REG, 541);
#endif

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
	for (size_t i = 0; str[i] != '\0'; i++) {
		if (str[i] == '\n')
			uart_putc('\r');
		uart_putc((unsigned char)str[i]);
	}
}

char *uart_gets()
{
	static char str[MAX_INPUT_LENGTH + 1];
	int i = 0;

	/* Initialize input string with null terminators */
	memset(&str, '\0', MAX_INPUT_LENGTH + 1);

	/* Get up to console's maximum length chars */
	for (i = 0; i < MAX_INPUT_LENGTH; i++) {
		/* Get char from serial, echo back */
		str[i] = (char) uart_getc();
		uart_putc(str[i]);
		/* If we get a NL or CR, break */
		if (str[i] == '\r' || str[i] == '\n') {
			break;
		}
	}
	/* Always append a null terminator at end of string */
	str[i] = '\0';

	return str;
}

void handle_uart_irq()
{
	unsigned char c;

	/* While the receiver holds a valid bit (on Read) */
	while ((mmio_read(AUX_MU_IIR_REG) & (1 << 2)) == (1 << 2)) {
		c = uart_getc();
		if (c == '\r') {
			/* When user presses Enter a CR is returned */
			uart_putc(c);
			uart_putc('\n');
		}
		else {
			uart_putc(c);
		}
	}
}