/**
 * @file timer.h
 * @brief Definition of System Timer registers addresses
 */

#ifndef P_TIMER_H
#define P_TIMER_H

#include <peripherals/base.h>

/** System's Timer Clock Frequency (for delays in sec). */
#define TIMER_CLK_HZ 1000000
/** System's Timer Clock Frequency / 1000 (for delays in msec). */
#define TIMER_CLK_1000_HZ 1000

/**
 * System Timer registers
 */
enum
{

	/**
	 * The base address for System Timers.     \n
	 * For raspi 0,1: TIMER_BASE = 0x20003000; \n
	 * For raspi 4:   TIMER_BASE = 0xFE003000;
	 */
	TIMER_BASE = (MMIO_BASE + 0x3000),

	TIMER_CS  = (TIMER_BASE + 0x00), /**< System Timer Control/Status */
	TIMER_CLO = (TIMER_BASE + 0x04), /**< System Timer Counter Lower 32 bits */
	TIMER_CHI = (TIMER_BASE + 0x08), /**< System Timer Counter Higher 32 bits */
	TIMER_C0  = (TIMER_BASE + 0x0c), /**< System Timer Compare 0 */
	TIMER_C1  = (TIMER_BASE + 0x10), /**< System Timer Compare 1 */
	TIMER_C2  = (TIMER_BASE + 0x14), /**< System Timer Compare 2 */
	TIMER_C3  = (TIMER_BASE + 0x18), /**< System Timer Compare 3 */

	TIMER_CS_M0 = (1 << 0), /**< System Timer Match 0 */
	TIMER_CS_M1 = (1 << 1), /**< System Timer Match 1 */
	TIMER_CS_M2 = (1 << 2), /**< System Timer Match 2 */
	TIMER_CS_M3 = (1 << 3)  /**< System Timer Match 3 */
};

#endif