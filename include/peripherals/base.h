/**
 * \defgroup peripherals peripherals
 * Raspberry Pi Peripherals addresses.
 * @{
 * @file base.h
 * @brief Definition of base MMIO registers addresses.
 * @details MMIO : Memory Mapped IO
 */

#ifndef P_BASE_H
#define P_BASE_H

/**
 * The MMIO area base address
 */
enum
{
#ifdef MODEL_0
	/** For raspi 0,1: MMIO_BASE = 0x20000000; */
	MMIO_BASE = 0x20000000
#elif MODEL_2
	/** For raspi 2,3: MMIO_BASE = 0x3F000000 */
	MMIO_BASE = 0x3F000000
#elif MODEL_3
	/** For raspi 2,3: MMIO_BASE = 0x3F000000 */
	MMIO_BASE = 0x3F000000
#elif MODEL_4
	/** For raspi 4:   MMIO_BASE = 0xFE000000 */
	MMIO_BASE = 0xFE000000
#endif

};

/** @} */

#endif