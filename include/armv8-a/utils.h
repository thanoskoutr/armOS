/**
 * @file utils.h
 * @brief Definition of basic armv8-a assembly functions.
 */

#ifndef UTILS_H
#define UTILS_H

#include <stdint.h>

/**
 * Gets the Exception Level of the processor.
 * @see utils.S
 */
extern int get_el();

/**
 * Zeroes out a memory section.
 * @param src The start address of the section.
 * @param n The size of the section.
 * @details Zeroes out the section defined by the starting address on @a src
 * and the size of the section on @a n.
 * @see utils.S
 */
void memzero(uint64_t src, uint64_t n);

#endif