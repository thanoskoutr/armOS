/*
 * timer.h - Definition of System Timer registers addresses
 */

#ifndef P_TIMER_H
#define P_TIMER_H

#include <peripherals/base.h>

enum
{
	/* The base address for System Timer */
	/*
	 * TIMER_BASE
	 * For raspi 0,1: TIMER_BASE = 0x20003000;
	 * For raspi 4:   TIMER_BASE = 0xFE003000;
	 */
	TIMER_BASE = (MMIO_BASE + 0x3000),

	TIMER_CS  = (TIMER_BASE + 0x00),
	TIMER_CLO = (TIMER_BASE + 0x04),
	TIMER_CHI = (TIMER_BASE + 0x08),
	TIMER_C0  = (TIMER_BASE + 0x0c),
	TIMER_C1  = (TIMER_BASE + 0x10),
	TIMER_C2  = (TIMER_BASE + 0x14),
	TIMER_C3  = (TIMER_BASE + 0x18),

	TIMER_CS_M0 = (1 << 0),
	TIMER_CS_M1 = (1 << 1),
	TIMER_CS_M2 = (1 << 2),
	TIMER_CS_M3 = (1 << 3)
};

#endif