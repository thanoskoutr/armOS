/*
 * entry.h - Definition of armv6 Invalid exception type values.
 * Used to identify the invalid triggered exception.
 */

#ifndef ARM6_ENTRY_H
#define ARM6_ENTRY_H

#define EXCEPT_RESET 0
#define EXCEPT_UNDEFINED_INSTR 1
#define EXCEPT_SWI 2
#define EXCEPT_PREFECH_ABORT 3
#define EXCEPT_DATA_ABORT 4
#define EXCEPT_RESERVED 5
#define EXCEPT_IRQ 6
#define EXCEPT_FIQ 7

#endif