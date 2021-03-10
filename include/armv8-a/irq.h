/*
 * irq.h - Definition of armv8-a interrupt initialization functions.
 */

#ifndef IRQ_S_H
#define IRQ_S_H

void irq_vector_init();
void irq_enable();
void irq_disable();

#endif