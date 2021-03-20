/**
 * \defgroup string string
 * Small subset of string.h.
 * @{
 * @file string.h
 * @brief Definition of some string.h functions.
 */

#include <stddef.h>

#ifndef STRING_H
#define STRING_H

/**
 * Fills the first @a n bytes of the memory area pointed to by @a s
 * 	with the constant byte @a c.
 * @return A pointer to the memory area s.
 */
void *memset(void *s, int c, size_t n);

/**
 * Copies @a n bytes from memory area @a src to memory area @a dest.
 * 	The memory areas must not overlap.
 * @return A pointer to dest.
 */
void *memcpy(void *dest, const void *src, size_t n);

/**
 * Calculates the length of the string pointed to by @a s,
 * 	excluding the terminating null byte ('\0').
 * @param s A string pointer.
 * @return The number of bytes in the string pointed to by @a s.
 */
size_t strlen(const char *s);

/**
 * Compares the two strings @a s1 and @a s2.
 * @param s1 A string pointer.
 * @param s2 A string pointer.
 * @return An integer less than, equal to, or greater than 0 if @a s1 is found,
 * 	respectively, to be less than, to match, or be greater than @a s2.
 */
int strcmp(const char *s1, const char *s2);

/**
 * Copies the string pointed to by @a src, including the terminating null
 * 	byte ('\0'), to the buffer pointed to by @a dest.
 * @param dest A string pointer.
 * @param src A string pointer.
 * @return A pointer to the destination string @a dest.
 */
char *strcpy(char *dest, const char *src);

/**
 * Appends the @a src string to the @a dest string, overwriting the
 * 	terminating null byte ('\0') at the end of @a dest,
 * 	and then adds a terminating null byte.
 * @param dest A string pointer.
 * @param src A string pointer.
 * @return A pointer to the resulting string @a dest.
 */
char *strcat(char *dest, const char *src);

/**
 * Reverses a given string in place.
 * @param s A string pointer.
 * @see strlen()
 */
void strrev(char *s);

/** @} */

#endif