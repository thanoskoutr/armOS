/*
 * scheduler.S - Implementation of armv6 scheduler helper functions.
 */

#include <armv6/scheduler.h>

.globl ret_from_fork
ret_from_fork:
	/* A call to preempt_enable(), in order for the task to be rescheduled */
	bl schedule_tail
	/*
	 * Calls the process function stored in r1,
	 * with the argument stored in r2.
	 * (Registers convention set by fork.c)
	 */
	mov r0, r2
	mov lr, r1
	bx lr 	/* Should never return */

.globl cpu_switch_to
cpu_switch_to: