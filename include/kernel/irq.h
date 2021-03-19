/**
 * @file irq.h
 * @brief Definition of interrupt handling functions.
 */

#ifndef IRQ_H
#define IRQ_H

/**
 * Enables System Timer and UART interrupts.
 */
void enable_interrupt_controller();

#ifdef AARCH_32
/**
 * Prints information about the error, on an invalid exception.
 * @param type Type of exception, defined in include/armv6/entry.h
 */
void show_invalid_entry_message(int type);
#elif AARCH_64
/**
 * Prints information about the error, on an invalid exception.
 * @param type Type of exception, defined in include/armv8-a/entry.h
 * @param esr Exception Syndrome Register (ESR),
 * contains detailed information about what causes an exception.
 * @param address The address of the instruction that had been executed
 * when the exception was generated.
 */
void show_invalid_entry_message(int type, unsigned long esr, \
						unsigned long address);
#endif

/**
 * Exception handler for all IRQs.
 */
void handle_irq();


#endif