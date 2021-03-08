/*
 * printk.h - Definition of printk
 * Prints a kernel message to the serial console
 */

#include <stddef.h>
#include <stdarg.h>

#ifndef PRINTK_H
#define PRINTK_H


/*
 * strlen - calculates the length of the string pointed to by s,
 * 	excluding the terminating null byte ('\0').
 * @s: A string pointer.
 * Returns: The number of bytes in the string pointed to by s.
 */
size_t strlen(const char *s);;

/*
 * strrev - Reverses a given string in place.
 * @s: A string pointer.
 */
void strrev(char *s);

/*
 * itoa - Converts an int to a null-terminated string using the specified base.
 * @value: Value to be converted to a string.
 * @base: Numerical base used to represent the value as a string.
 * Where 10 means decimal base, 16 hexadecimal, 8 octal, and 2 binary.
 * Returns: A pointer to the resulting null-terminated string.
 */
/* Only base 10 supported for now */
char *itoa(int value);
// char *itoa(int value, int base);

/*
 * printk - print a kernel message
 * @fmt: format string
 * The formats supported by this implementation are: 'd' 'c' 's', 'x'.
 * To be supported: u', 'l', 'll'.
 */
int printk(const char *fmt, ...);


#endif