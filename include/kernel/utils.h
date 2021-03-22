/**
 * \ingroup entry8
 * @file utils.h
 * @brief Definition of basic ARM assembly functions.
 */

#ifndef UTILS_H
#define UTILS_H

#ifdef AARCH_32
#elif AARCH_64
/**
 * \ingroup entry8
 * Gets the Exception Level of the processor (For ARMv-8).
 */
extern int get_el();
#endif

#endif