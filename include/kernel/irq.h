/*
 * irq.h - Definition of interrupt handling functions.
 *
 */

#ifndef IRQ_H
#define IRQ_H

// #ifdef AARCH_32
// #elif AARCH_64

/*
 * Enables System Timer 1 interrupts
 */
void enable_interrupt_controller();

/*
 * Prints information about the error, on an invalid exception.
 */
void show_invalid_entry_message(int type, unsigned long esr, \
						unsigned long address);

/*
 * Exception handler for IRQ EL1t
 */
void handle_irq();
// #endif

#endif