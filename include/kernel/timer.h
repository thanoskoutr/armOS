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

#endif