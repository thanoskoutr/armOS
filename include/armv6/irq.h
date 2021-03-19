/**
 * @file irq.h
 * @brief Definition of armv6 interrupt initialization functions.
 */

#ifndef ARM6_IRQ_S_H
#define ARM6_IRQ_S_H

/**
 * Initializes interrupts, by moving the exception vector at address 0x0.
 */
void irq_vector_init();
/** Enables (Unmasks) interrupts. */
void irq_enable();
/** Disables (Masks) interrupts. */
void irq_disable();

#endif