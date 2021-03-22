/**
 * \ingroup exceptions
 * @file irq.h
 * @brief Definition of armv6 interrupt initialization functions.
 */

#ifndef ARM6_IRQ_S_H
#define ARM6_IRQ_S_H

/**
 * \ingroup exceptions
 * Initializes interrupts, by moving the exception vector at address 0x0.
 */
void irq_vector_init();
/**
 * \ingroup exceptions
 * Enables (Unmasks) interrupts.
 */
void irq_enable();
/**
 * \ingroup exceptions
 * Disables (Masks) interrupts.
 */
void irq_disable();

#endif