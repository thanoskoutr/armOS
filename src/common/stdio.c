/*
 * stdio.c - Implementation of some basic <stdio.h> functions from libC.
 */

#include <kernel/uart.h>

/*
 * putc - put byte on a stream
 * A wrapper for uart_putc(), needed for printf()
 */
void putc (void* p, char c)
{
	// Useless p
	(void) p;
	uart_putc(c);
}