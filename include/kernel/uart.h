/**
 * \defgroup drivers drivers
 * Drivers for Raspberry Pi Peripherals.
 * @{
 * @file uart.h
 * @brief Definition of basic UART functions.
 */

#ifndef UART_H
#define UART_H

/**
 * Maximum length for the serial input.
 * @warning It is a temporary solution, because of no support for dynamic allocation of memory.
 * @see console(), uart_gets(), process.c
 */
#define MAX_INPUT_LENGTH 80

/**
 * Initializes the UART interface based on the running device.
 * @details Basic configuration:
 * - Sets Alternative Function 5 for GPIO pins 14, 15, in order to enable mini UART.
 * - Disables pull up/down resistors for pins 14, 15.
 * - Enables mini UART.
 * - Disables auto flow control and disables receiver and transmitter.
 * - Enables receive and transmit interrupts.
 * - Clears the receive and transmit FIFO, and enables FIFO.
 * - Enables 8 bit mode.
 * - Sets RTS line to be always high.
 * - Sets baud rate at 115200.
 * - Enables transmitter and receiver.
 *
 * @see peripherals/gpio.h, peripherals/aux.h
 */
void uart_init();

/**
 * Sends a byte to the UART (serial output).
 * @param c The byte sent to the UART.
 * @details First waits for the UART to become ready to transmit,
 * and then writes the byte @a c to the @ref AUX_MU_IO_REG register.
 * @see peripherals/aux.h
 */
void uart_putc(unsigned char c);

/**
 * Gets a byte to the UART (serial input).
 * @return The byte received from the UART.
 * @details First waits for the UART to have received something,
 * and then reads the contents of the @ref AUX_MU_IO_REG register
 * @see peripherals/aux.h
 */
unsigned char uart_getc();

/**
 * Sends a string to the UART (serial output).
 * @param str A string pointer for the string to send to the UART.
 * @details Iterates over the string and prints each char to the serial output.
 * @note If a new New Line (`\n`) char is found, it appends a Carriage Return (`\r`) char,
 * so there is no need to include the `\r` char in the @a str string.
 * @see uart_putc()
 */
void uart_puts(const char* str);

/**
 * Gets a string from the UART (serial input).
 * @return A pointer to a static char array, that the string is saved.
 * @details Reads in a loop a byte from the serial input using the uart_getc()
 * function until a New Line (`\n`) or a Carriage Return (`\r`) char is received.
 * Echoes back each char to the serial output.
 * @note Gets up to @ref MAX_INPUT_LENGTH chars.
 * @note Always appends a null terminator (`\0`) at the end of the string.
 * @see uart_getc(), MAX_INPUT_LENGTH
 */
char *uart_gets();

/** @} */

/**
 * \ingroup exceptions
 * Exception handler for the UART (Asynchronous read from the serial input).
 * @details Gets called when an interrupt is triggered from the UART.
 * While the receiver holds a valid bit, reads the byte and echoes back.
 * @note If a Carriage Return (`\r`) char is found, it appends a New Line (`\n`) char.
 * @see handle_irq(), uart_getc(), uart_putc()
 */
void handle_uart_irq();

#endif