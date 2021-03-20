/**
 * @file timer.h
 * @brief Definition of basic System Timer functions.
 */

#ifndef TIMER_H
#define TIMER_H

#include <stdint.h>

/**
 * The pulse time in milliseconds for the LED IRQ.
 */
#define LED_MSEC_IRQ 200

/**
 * Initializes System Timer 1, with a time interval of msec milliseconds.
 * @param msec Time interval in milliseconds.
 */
void timer_1_init(uint32_t msec);
/**
 * Initializes System Timer 3, with a time interval of msec milliseconds.
 * @param msec Time interval in milliseconds.
 */
void timer_3_init(uint32_t msec);

/**
 * Disables System Timer 1.
 */
void timer_1_stop();
/**
 * Disables System Timer 3.
 */
void timer_3_stop();

/**
 * Exception handler for System Timer 1.
 * @details Gets called when an interrupt is triggered from the System Timer 1.
 * - Updates current counter value, for next interrupt with the same interval ( @ref interval_1).
 * - Set this value to be compared for System Timer 1 Interrupt.
 * - Acknowledges the interrupt by writing 1 to the @ref TIMER_CS register
 * - Calls led_on_ms(), to pulse the LED for a small interval.
 *
 * @see handle_irq(), led_on_ms()
 */
void handle_timer_1_irq();
/**
 * Exception handler for System Timer 3.
 * @details Gets called when an interrupt is triggered from the System Timer 3.
 * - Updates current counter value, for next interrupt with the same interval ( @ref interval_3).
 * - Set this value to be compared for System Timer 3 Interrupt.
 * - Acknowledges the interrupt by writing 1 to the @ref TIMER_CS register
 * - Calls timer_tick() for the scheduler.
 *
 * @see handle_irq(), timer_tick()
 */
void handle_timer_3_irq();

/**
 * Reads the 64-bit free running counter value that contains,
 * the number of ticks since the system's initialization.
 * @return Number of ticks.
 */
uint64_t timer_get_ticks();

/**
 * Sleeps for msec milliseconds, using the timers free running counter.
 * @param msec Time interval in milliseconds.
 * @note Blocking function.
 */
void timer_msleep (uint32_t msec);

#endif