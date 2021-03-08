/*
 * stdlib.h - Implementation of some stdlib.h functions
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