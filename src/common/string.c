/**
 * \ingroup string
 * Implementation of a small subset of string.h.
 * @{
 * @file string.c
 * @brief Implementation of some string.h functions
 */

#include <stddef.h>
#include <common/string.h>

void *memset(void *s, int c, size_t n)
{
	unsigned char *dst = s;

	/* Fill n bytes of s with c */
	while (n > 0) {
		*dst = (unsigned char) c;
		dst++;
		n--;
	}
	return s;
}

void *memcpy(void *dest, const void *src, size_t n)
{
	/* Typecast src and dest addresses to correct data types */
	char *d = (char *) dest;
	const char *s = (const char *) src;

	/* Copy contents of *src, to *dest */
	while (n > 0) {
		*(d++) = *(s++);
		n--;
	}
	return dest;
}

size_t strlen(const char *s)
{
	const char *char_ptr;

	/* Iterate string until null terminator */
	for (char_ptr = s; *char_ptr; ++char_ptr)
		;
	/* Return the difference of (end - start) address -> length of string */
	return (char_ptr - s);
}

int strcmp(const char *s1, const char *s2)
{
	while((*s1 != '\0') && (*s1 == *s2)) {
		s1++;
		s2++;
	}

	/* Return the ASCII difference after convert. char* to unsigned char* */
	return *(const unsigned char*) s1 - *(const unsigned char*) s2;
}

char *strcpy(char *dest, const char *src)
{
	/* Return if no memory is allocated to the destination */
	if (dest == NULL)
		return NULL;

	char *tmp = dest;

	/* Copy the string pointed to by src, in dest */
	while (*src != '\0') {
		*(tmp++) = *(src++);
	}
	/* Include null terminator */
	*tmp = '\0';

	/* Return starting address of dest */
	return dest;

}

char *strcat(char *dest, const char *src)
{
	char *tmp = dest;

	/* Move dest pointer to the end of string */
	while (*tmp != '\0')
		tmp++;

	/* Appends characters of source to the destination string */
	while (*src != '\0') {
		*(tmp++) = *(src++);
	}
	/* Include null terminator */
	*tmp = '\0';

	/* Return starting address of dest */
	return dest;
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

/** @} */