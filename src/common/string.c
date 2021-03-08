/*
 * string.c - Implementation of some string.h functions
 */

#include <stddef.h>
#include <common/string.h>

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