/*
 * string.h - Definition of some string.h functions
 */

#include <stddef.h>

#ifndef STRING_H
#define STRING_H

/*
 * memset - Fills the first n bytes of the memory area pointed to by s
 * 	with the constant byte c.
 * Returns: A pointer to the memory area s.
 */
void *memset(void *s, int c, size_t n);

/*
 * memcpy - Copies n bytes from memory area src to memory area dest.
 * 	The memory areas must not overlap.
 * Returns: A pointer to dest.
 */
void *memcpy(void *dest, const void *src, size_t n);

/*
 * strlen - Calculates the length of the string pointed to by s,
 * 	excluding the terminating null byte ('\0').
 * @s: A string pointer.
 * Returns: The number of bytes in the string pointed to by s.
 */
size_t strlen(const char *s);

/*
 * strcmp - Compares the two strings s1 and s2.
 * @s1: A string pointer.
 * @s2: A string pointer.
 * Returns: An integer less than, equal to, or greater than 0 if s1 is found,
 * 	respectively, to be less than, to match, or be greater than s2.
 */
int strcmp(const char *s1, const char *s2);

/*
 * strcpy - Copies the string pointed to by src, including the terminating null
 * 	byte ('\0'), to the buffer pointed to by dest.
 * @dest: A string pointer.
 * @src: A string pointer.
 * Returns: A pointer to the destination string dest.
 */
char *strcpy(char *dest, const char *src);

/*
 * strcat - Appends the src string to the dest string, overwriting the
 * 	terminating null byte ('\0') at the end of dest,
 * 	and then adds a terminating null byte.
 * @dest: A string pointer.
 * @src: A string pointer.
 * Returns: A pointer to the resulting string dest.
 */
char *strcat(char *dest, const char *src);

/*
 * strrev - Reverses a given string in place.
 * @s: A string pointer.
 */
void strrev(char *s);

#endif