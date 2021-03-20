/**
 * \defgroup stdbool stdbool
 * The stdbool.h header.
 * @{
 * @file stdbool.h
 * @brief Definition of boolean type and values.
 */

#ifndef STDBOOL_H
#define STDBOOL_H

/**
 * Booleans expand to integer constants 0, 1.
 */
typedef enum {
	false = 0,	/**< 0 */
	true = 1	/**< 1 */
} bool;

/** @} */

#endif