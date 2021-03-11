/*
 * timer.c - Implementation of basic System Timer functions
 */

#include <stdint.h>

#include <kernel/mmio.h>
#include <kernel/printk.h>

#include <peripherals/timer.h>

const uint32_t interval_1 = 2000000;	/* Every ~2 sec */
const uint32_t interval_3 = 4000000;	/* Every ~4 sec */
uint32_t cur_val_1 = 0;
uint32_t cur_val_3 = 0;

void timer_init()
{
	/* Read current counter value */
	cur_val_1 = mmio_read(TIMER_CLO);

	/* Increase it by an interval */
	cur_val_1 += interval_1;

	/* Set this value to be compared for System Timer 1 Interrupt */
	mmio_write(TIMER_C1, cur_val_1);

	/* Read current counter value */
	cur_val_3 = mmio_read(TIMER_CLO);

	/* Increase it by an interval */
	cur_val_3 += interval_3;

	/* Set this value to be compared for System Timer 3 Interrupt */
	mmio_write(TIMER_C3, cur_val_3);

}

void handle_timer_1_irq()
{
	/* Update current counter value, for next interrupt at same interval */
	cur_val_1 += interval_1;

	/* Set this value to be compared for System Timer 1 Interrupt */
	mmio_write(TIMER_C1, cur_val_1);

	/* Acknowledge the interrupt by writing 1 to the TIMER_CS register */
	uint32_t timer_cs_1 = mmio_read(TIMER_CS);
	timer_cs_1 |= TIMER_CS_M1;
	mmio_write(TIMER_CS, timer_cs_1);

	// printk("Timer 1 Interrupt received\n");
}

void handle_timer_3_irq()
{
	/* Update current counter value, for next interrupt at same interval */
	cur_val_3 += interval_3;

	/* Set this value to be compared for System Timer 3 Interrupt */
	mmio_write(TIMER_C3, cur_val_3);

	/* Acknowledge the interrupt by writing 1 to the TIMER_CS register */
	uint32_t timer_cs_3 = mmio_read(TIMER_CS);
	timer_cs_3 |= TIMER_CS_M3;
	mmio_write(TIMER_CS, timer_cs_3);

	// printk("Timer 3 Interrupt received\n");
}
