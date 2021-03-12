/*
 * irq.h - Definition of armv6 interrupt initialization functions.
 */

#ifndef ARM6_IRQ_S_H
#define ARM6_IRQ_S_H

void irq_vector_init();
void irq_enable();
void irq_disable();

#endif