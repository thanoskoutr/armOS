/*
 * base.h - Definition of base MMIO registers addresses
 * MMIO: Memory Mapped IO
 */

#ifndef P_BASE_H
#define P_BASE_H

enum
{
	/* The MMIO area base address */
	/*
	 * For raspi 0,1: MMIO_BASE = 0x20000000;
	 * For raspi 2,3: MMIO_BASE = 0x3F000000;
	 * For raspi 4:   MMIO_BASE = 0xFE000000;
	 */

#ifdef MODEL_0
	MMIO_BASE = 0x20000000
#elif MODEL_2
	MMIO_BASE = 0x3F000000
#elif MODEL_3
	MMIO_BASE = 0x3F000000
#elif MODEL_4
	MMIO_BASE = 0xFE000000
#endif

};

#endif