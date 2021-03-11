/*
 * timer.c - Definition of basic System Timer functions
 */

#ifndef TIMER_H
#define TIMER_H

/*
 * Initializes System Timer
 */
void timer_init();

/*
 * Exception handler for System Timers 1, 3
 */
void handle_timer_1_irq();
void handle_timer_3_irq();

/*
 * Reads the 64-bit free running counter value that contains,
 * the number of ticks since the system's initialization.
 * Returns the number of ticks.
 */
uint64_t timer_get_ticks();

/*
 * Sleeps for msec milliseconds, using the timers free running counter.
 */
void timer_msleep (uint32_t msec);

#endif