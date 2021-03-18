/**
 * \defgroup entry8 entry
 * Exception type values - ARMv8-a
 * @{
 * @file entry.h
 * @brief Definition of armv8-a Invalid exception type values.
 * @details Used to identify the invalid triggered exception.
 */

#ifndef ARM8_ENTRY_H
#define ARM8_ENTRY_H

/** \name Registers
 * Size of all saved registers (31 8byte registes)
 */
#define S_FRAME_SIZE		256

/**
 * \name EL1t
 * @{
 * For exceptions taken from EL1 while
 * 	stack pointer was shared with EL0
 */
#define SYNC_INVALID_EL1t	0
#define IRQ_INVALID_EL1t	1
#define FIQ_INVALID_EL1t	2
#define ERROR_INVALID_EL1t	3
/* @} */

/**
 * \name EL1h
 * @{
 * For exceptions taken from EL1 at the time when dedicated
 * 	stack pointer was allocated for EL1.
 */
#define SYNC_INVALID_EL1h	4
#define IRQ_INVALID_EL1h	5
#define FIQ_INVALID_EL1h	6
#define ERROR_INVALID_EL1h	7
/* @} */

/**
 * \name EL0_64
 * @{
 * For exceptions taken from EL0, while executing in 64-bit mode.
 */
#define SYNC_INVALID_EL0_64	8
#define IRQ_INVALID_EL0_64	9
#define FIQ_INVALID_EL0_64	10
#define ERROR_INVALID_EL0_64	11
/* @} */

/**
 * \name EL0_32
 * @{
 * For exceptions taken from EL0, while executing in 32-bit mode.
 */
#define SYNC_INVALID_EL0_32	12
#define IRQ_INVALID_EL0_32	13
#define FIQ_INVALID_EL0_32	14
#define ERROR_INVALID_EL0_32	15
/* @} */


/* @} */

#endif