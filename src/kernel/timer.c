/*
 * timer.c - Implementation of basic System Timer functions
 */

#include <stdint.h>

#include <kernel/mmio.h>
#include <kernel/printk.h>
#include <kernel/led.h>

#include <peripherals/timer.h>

uint32_t interval_1;
uint32_t interval_3;
uint32_t cur_val_1 = 0;
uint32_t cur_val_3 = 0;

void timer_1_init(uint32_t msec)
{
	/* Set time interval to be msec milliseconds */
	interval_1 = msec * TIMER_CLK_1000_HZ;
	/* Read current counter value */
	cur_val_1 = mmio_read(TIMER_CLO);
	/* Increase it by an interval */
	cur_val_1 += interval_1;
	/* Set this value to be compared for System Timer 1 Interrupt */
	mmio_write(TIMER_C1, cur_val_1);
}

void timer_3_init(uint32_t msec)
{
	/* Set time interval to be msec milliseconds */
	interval_3 = msec * TIMER_CLK_1000_HZ;
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

	// printk("\nTimer 1 Interrupt received\n");
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

	// printk("\nTimer 3 Interrupt received\n");
}

uint64_t timer_get_ticks()
{
	uint32_t counter_hi = mmio_read(TIMER_CHI);
	uint32_t counter_lo = mmio_read(TIMER_CLO);

	/* Check if high value didn't change, after setting it */
	while (counter_hi != mmio_read(TIMER_CHI)) {
		counter_hi = mmio_read(TIMER_CHI);
		counter_lo = mmio_read(TIMER_CLO);
	}

	/* Create the full 64-bit counter value */
	uint64_t counter = ((uint64_t) counter_hi << 32) | counter_lo;

	return counter;

}

void timer_msleep (uint32_t msec)
{
	/* Get counters current calue */
	uint64_t start = timer_get_ticks();

	/* Wait until msec have passed from start */
	while (timer_get_ticks() < start + (msec * 1000)) {
		;
	}
}
