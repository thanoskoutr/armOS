/**
 * \ingroup exceptions
 * @file irq.h
 * @brief Definition of armv8-a interrupt initialization functions.
 */

#ifndef ARM8_IRQ_S_H
#define ARM8_IRQ_S_H

/**
 * Initializes interrupts, by setting the address of the Vector Base Address
 * Register (vbar_el1) to our vector table address.
 */
void irq_vector_init();
/** Enables (Unmasks) interrupts. */
void irq_enable();
/** Disables (Masks) interrupts. */
void irq_disable();

#endif