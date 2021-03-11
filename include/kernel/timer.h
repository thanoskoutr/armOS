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
 * Exception handler for System Timer
 */
void handle_timer_irq();

#endif