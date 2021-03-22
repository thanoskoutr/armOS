/**
 * \ingroup peripherals
 * @file irq.h
 * @brief Definition of IRQ registers addresses
 * @details IRQ : Interrupt Request
 */

#ifndef P_IRQ_H
#define P_IRQ_H

#include <peripherals/base.h>

/**
 * \ingroup peripherals
 * The base address for IRQ
 */
enum
{

	/**
	 * The base address for IRQ.             \n
	 * For raspi 0,1: IRQ_BASE = 0x2000B000; \n
	 * For raspi 4:   IRQ_BASE = 0xFE00B000;
	 */
	IRQ_BASE = (MMIO_BASE + 0xB000),

	/* The offsets for reach register for the IRQ */
#if defined(MODEL_0) || defined(MODEL_2) || defined(MODEL_3)
	/* Broadcom 2835, 2836, 2837 specific IRQ registers */
	IRQ0_PENDING_0     = (IRQ_BASE + 0x200), /**< IRQ basic pending  */
	IRQ0_PENDING_1     = (IRQ_BASE + 0x204), /**< IRQ pending 1      */
	IRQ0_PENDING_2     = (IRQ_BASE + 0x208), /**< IRQ pending 2      */
	FIQ_CONTROL        = (IRQ_BASE + 0x20C), /**< FIQ control        */
	IRQ0_SET_EN_1      = (IRQ_BASE + 0x210), /**< Enable IRQs 1      */
	IRQ0_SET_EN_2      = (IRQ_BASE + 0x214), /**< Enable IRQs 2      */
	IRQ0_SET_EN_0      = (IRQ_BASE + 0x218), /**< Enable Basic IRQs  */
	IRQ0_CLR_EN_1      = (IRQ_BASE + 0x21C), /**< Disable IRQs 1     */
	IRQ0_CLR_EN_2      = (IRQ_BASE + 0x220), /**< Disable IRQs 2     */
	IRQ0_CLR_EN_0      = (IRQ_BASE + 0x224), /**< Disable Basic IRQs */

#elif defined(MODEL_4)
	/* Broadcom 2711 specific IRQ registers */
	IRQ0_PENDING_0     = (IRQ_BASE + 0x200), /**< ARM Core 0 IRQ Enabled Interrupt Pending bits [31:0] */
	IRQ0_PENDING_1     = (IRQ_BASE + 0x204), /**< ARM Core 0 IRQ Enabled Interrupt pending bits [63:32] */
	IRQ0_PENDING_2     = (IRQ_BASE + 0x208), /**< ARM Core 0 IRQ Enabled Interrupt pending bits [79:64] */
	IRQ0_SET_EN_0      = (IRQ_BASE + 0x210), /**< Write to Set ARM Core 0 IRQ enable bits [31:0] */
	IRQ0_SET_EN_1      = (IRQ_BASE + 0x214), /**< Write to Set ARM Core 0 IRQ enable bits [63:32] */
	IRQ0_SET_EN_2      = (IRQ_BASE + 0x218), /**< Write to Set ARM Core 0 IRQ enable bits[79:64] */
	IRQ0_CLR_EN_0      = (IRQ_BASE + 0x220), /**< Write to Clear ARM Core 0 IRQ enable bits [31:0] */
	IRQ0_CLR_EN_1      = (IRQ_BASE + 0x224), /**< Write to Clear ARM Core 0 IRQ enable bits [63:32] */
	IRQ0_CLR_EN_2      = (IRQ_BASE + 0x228), /**< Write to Clear ARM Core 0 IRQ enable bits [79:64] */
#endif

	/** The AUX bit for enabling/disabling AUX interrupts */
	AUX_IRQ = (1 << 29),

	SYSTEM_TIMER_IRQ_0 = (1 << 0), /**< The System Timer 0 bit for enabling/disabling timer interrupts */
	SYSTEM_TIMER_IRQ_1 = (1 << 1), /**< The System Timer 1 bit for enabling/disabling timer interrupts */
	SYSTEM_TIMER_IRQ_2 = (1 << 2), /**< The System Timer 2 bit for enabling/disabling timer interrupts */
	SYSTEM_TIMER_IRQ_3 = (1 << 3)  /**< The System Timer 3 bit for enabling/disabling timer interrupts */
};

#endif