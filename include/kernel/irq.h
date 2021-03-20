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
 * @see include/armv6/entry.h
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
 * @see include/armv8-a/entry.h
 */
void show_invalid_entry_message(int type, unsigned long esr, \
						unsigned long address);
#endif

/**
 * Exception handler for all IRQs.
 * @details Reads from the interrupt pending registers ( @ref IRQ0_PENDING_0 or
 *  @ref IRQ0_PENDING_1), and if a valid value is found we have an interrupt.
 * Checks each bit for the interrupts we have enabled, and if it is set,
 * it removes the bit we handled and calls the corresponding handler.
 * @see handle_timer_1_irq(), handle_timer_3_irq(), handle_uart_irq()
 */
void handle_irq();


#endif