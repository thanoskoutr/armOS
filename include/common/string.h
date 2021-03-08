/*
 * string.h - Definition of some string.h functions
 */

#include <stddef.h>

#ifndef STRING_H
#define STRING_H

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

#endif