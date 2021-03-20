/**
 * \ingroup stdlib
 * Implementation of a small subset of stdlib.h.
 * @{
 * @file stdlib.c
 * @brief Implementation of some stdlib.h functions
 */

#include <common/stdlib.h>
#include <common/string.h>

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

int atoi(const char *str)
{
	/* The converted number to be returned */
	int num = 0;

	/*
	 *Loop till we have reached end of the string
	 * or current character is non-numeric.
	 */
	while ((*str != '\0') && (*str >= '0' && *str <= '9')) {
		num = num * 10 + (*str - '0');
		str++;
	}
	return num;
}

/** @} */