/*
 * stdlib.h - Definition of some stdlib.h functions
 */

#ifndef STDLIB_H
#define STDLIB_H

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


#endif