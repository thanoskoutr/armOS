/*
 * irq.h - Definition of IRQ registers addresses
 * IRQ: Interrupt Request
 */

#ifndef P_IRQ_H
#define P_IRQ_H

#include <peripherals/base.h>

enum
{
	/* The base address for IRQ */
	/*
	 * IRQ_BASE
	 * For raspi 0,1: IRQ_BASE = 0x2000B000;
	 * For raspi 4:   IRQ_BASE = 0xFE00B000;
	 */
	IRQ_BASE = (MMIO_BASE + 0xB000),

	/* The offsets for reach register for the IRQ */
#if defined(MODEL_0) || defined(MODEL_2) || defined(MODEL_3)
	/* Broadcom 2835, 2836, 2837 specific IRQ registers */
	IRQ0_PENDING_0     = (IRQ_BASE + 0x200),
	IRQ0_PENDING_1     = (IRQ_BASE + 0x204),
	IRQ0_PENDING_2     = (IRQ_BASE + 0x208),
	FIQ_CONTROL        = (IRQ_BASE + 0x20C),
	IRQ0_SET_EN_1      = (IRQ_BASE + 0x210),
	IRQ0_SET_EN_2      = (IRQ_BASE + 0x214),
	IRQ0_SET_EN_0      = (IRQ_BASE + 0x218),
	IRQ0_CLR_EN_1      = (IRQ_BASE + 0x21C),
	IRQ0_CLR_EN_2      = (IRQ_BASE + 0x220),
	IRQ0_CLR_EN_0      = (IRQ_BASE + 0x224),

	/*
	IRQ_BASIC_PENDING  = (IRQ_BASE + 0x200),
	IRQ_PENDING_1      = (IRQ_BASE + 0x204),
	IRQ_PENDING_2      = (IRQ_BASE + 0x208),
	FIQ_CONTROL        = (IRQ_BASE + 0x20C),
	ENABLE_IRQS_1      = (IRQ_BASE + 0x210),
	ENABLE_IRQS_2      = (IRQ_BASE + 0x214),
	ENABLE_BASIC_IRQS  = (IRQ_BASE + 0x218),
	DISABLE_IRQS_1     = (IRQ_BASE + 0x21C),
	DISABLE_IRQS_2     = (IRQ_BASE + 0x220),
	DISABLE_BASIC_IRQS = (IRQ_BASE + 0x224),
	*/

#elif defined(MODEL_4)
	/* Broadcom 2711 specific IRQ registers */
	IRQ0_PENDING_0     = (IRQ_BASE + 0x200),
	IRQ0_PENDING_1     = (IRQ_BASE + 0x204),
	IRQ0_PENDING_2     = (IRQ_BASE + 0x208),
	IRQ0_SET_EN_0      = (IRQ_BASE + 0x210),
	IRQ0_SET_EN_1      = (IRQ_BASE + 0x214),
	IRQ0_SET_EN_2      = (IRQ_BASE + 0x218),
	IRQ0_CLR_EN_0      = (IRQ_BASE + 0x220),
	IRQ0_CLR_EN_1      = (IRQ_BASE + 0x224),
	IRQ0_CLR_EN_2      = (IRQ_BASE + 0x228),
#endif

	/* The AUX bit for enabling/disabling AUX interrupts */
	AUX_IRQ = (1 << 29),

	/* The System Timer bits for enabling/disabling timer interrupts */
	SYSTEM_TIMER_IRQ_0 = (1 << 0),
	SYSTEM_TIMER_IRQ_1 = (1 << 1),
	SYSTEM_TIMER_IRQ_2 = (1 << 2),
	SYSTEM_TIMER_IRQ_3 = (1 << 3)
};

#endif