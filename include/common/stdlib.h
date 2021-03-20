/**
 * \defgroup stdlib stdlib
 * Small subset of stdlib.h.
 * @{
 * @file stdlib.h
 * @brief Definition of some stdlib.h functions
 */

#ifndef STDLIB_H
#define STDLIB_H

/**
 * Converts an int (Only base 10 supported for now)
 * to a null-terminated string using the specified base.
 * @param value Value to be converted to a string.
 * @return A pointer to the resulting null-terminated string.
 */
char *itoa(int value);
/*
 * Converts an int to a null-terminated string using the specified base.
 * @param value Value to be converted to a string.
 * @param base Numerical base used to represent the value as a string.
 * Where 10 means decimal base, 16 hexadecimal, 8 octal, and 2 binary.
 * (Only base 10 supported for now)
 * @return A pointer to the resulting null-terminated string.
 */
// char *itoa(int value, int base);

/**
 * Converts a string to an int
 * @param str This is the string representation of an integral number.
 * @return The converted integral number as an int value.
 * 	If no valid conversion could be performed, it returns zero.
 */
int atoi(const char *str);

/** @} */

#endif