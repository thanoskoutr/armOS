/*
 * printk.c - Implementation of printk
 * Prints a kernel message to the serial console
 */

#include <stddef.h>
#include <stdarg.h>
#include <kernel/printk.h>
#include <kernel/uart.h>

size_t strlen(const char *s)
{
	const char *char_ptr;

	/* Iterate string until null terminator */
	for (char_ptr = s; *char_ptr; ++char_ptr)
		;
	/* Return the difference of (end - start) address -> length of string */
	return (char_ptr - s);
}

void strrev(char *s)
{
	int i, j;
	char tmp;

	/* Reverse s string, char by char, using temp char */
	for (i = 0, j = strlen(s) - 1; i < j; i++, j--) {
		tmp = s[i];
		s[i] = s[j];
		s[j] = tmp;
	}
}

char *itoa(int value)
{
	int i, sign;
	/* Declare as static in order to return it */
	static char s[21];	/* Biggest int, 10 digits long */

	/* Record sign */
	if ((sign = value) < 0)
		/* Make positive */
		value = -value;
	i = 0;
	/* Generate digits in reverse order */
	do {
		s[i] = value % 10 + '0';
		i++;	/* Get next digit */
	} while ((value /= 10) > 0);

	if (sign < 0) {
		s[i] = '-';
		i++;
	}
	s[i] = '\0';

	/* Reverse string in place */
	strrev(s);

	return s;
}

int printk(const char *fmt, ...)
{
	va_list ap;

	/* Determine required size */
	va_start(ap, fmt);

	/* Iterate over format string */
	while (*fmt != '\0') {
		/* If a conversion specification is found */
		if (*fmt == '%') {
			/* Find the conversion specifier */
			switch (*(++fmt)) {
			case '%':
				uart_putc('%');
				break;
			case 'x':
				/*
				 * Pull of the argument and
				 * Convert int to char* (string)
				 * Print string
				 */
				uart_puts(itoa(va_arg(ap, unsigned int)));
				break;
			case 'd':
				uart_puts(itoa(va_arg(ap, int)));
				break;
			case 'c':
				uart_putc(va_arg(ap, int));
				break;
			case 's':
				uart_puts(va_arg(ap, const char *));
				break;
			default:
				break;
			}
		}
		/* If new line, add carriage return */
		else if (*fmt == '\n') {
			uart_putc('\r');
			uart_putc('\n');
		}
		/* Else print the other characters */
		else {
			uart_putc(*fmt);
		}
		fmt++;
	}

	/* clean memory reserved for ap */
	va_end(ap);

	return 0;
}