/**
 * \defgroup entry6 entry
 * Exception type values - ARMv6
 * @{
 * @file entry.h
 * @brief Definition of armv6 Invalid exception type values.
 * @details Used to identify the invalid triggered exception.
 */

#ifndef ARM6_ENTRY_H
#define ARM6_ENTRY_H

/** Hardware Reset. */
#define EXCEPT_RESET 0
/** Attempted to execute a meaningless instruction. */
#define EXCEPT_UNDEFINED_INSTR 1
/** Software wants to execute a privileged operation. */
#define EXCEPT_SWI 2
/** Bad memory access of an instruction. */
#define EXCEPT_PREFECH_ABORT 3
/** Bad memory access of data. */
#define EXCEPT_DATA_ABORT 4
/** Reserved. */
#define EXCEPT_RESERVED 5
/** Hardware wants to make the CPU aware of something. */
#define EXCEPT_IRQ 6
/** One select hardware can do the above faster than all others. */
#define EXCEPT_FIQ 7
/** @} */

#endif