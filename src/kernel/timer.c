/*
 * timer.c - Implementation of basic System Timer functions
 */

#include <stdint.h>

#include <kernel/mmio.h>
#include <kernel/printk.h>

#include <peripherals/timer.h>

const uint32_t interval = 200000;
uint32_t cur_val = 0;

void timer_init()
{
	/* Read current counter value */
	cur_val = mmio_read(TIMER_CLO);

	/* Increase it by an interval */
	cur_val += interval;

	/* Set this value to be compared for System Timer 1 Interrupt */
	mmio_write(TIMER_C1, cur_val);

}

void handle_timer_irq()
{
	/* Update current counter value, for next interrupt at same interval */
	cur_val += interval;

	/* Set this value to be compared for System Timer 1 Interrupt */
	mmio_write(TIMER_C1, cur_val);

	/* Acknowledge the interrupt by writing 1 to the TIMER_CS register */
	mmio_write(TIMER_CS, TIMER_CS_M1);

	// printk("Timer 1 Interrupt received\n");
}