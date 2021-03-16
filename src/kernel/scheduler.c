/*
 * scheduler.c - Implementation of scheduler functions
 */

#include <stdint.h>
#include <stddef.h>

#include <kernel/scheduler.h>
#include <kernel/printk.h>

#ifdef AARCH_32
#include <armv6/irq.h>
#elif AARCH_64
#include <armv8-a/irq.h>
#endif


/*
 * init_task: The first task that is run on kernel startup
 * current: Holds a pointer to the init_task
 * task: Appends a pointer to the init_task
 */
static task_struct init_task = INIT_TASK;
task_struct *current = &(init_task);
task_struct *task[NR_TASKS] = {&(init_task), };

/* Number of currently running tasks = 1 (init_task) */
int nr_tasks = 1;


void preempt_disable()
{
	current->preempt_count++;
}

void preempt_enable()
{
	current->preempt_count--;
}

void schedule_tail()
{
	preempt_enable();
}

void switch_to(task_struct * next)
{
	/* Check that the next process is not the same as the current */
	if (current == next)
		return;
	/* If not, update the current process as the next */
	task_struct *prev = current;
	current = next;
	/* Call cpu_switch_to, for context switch */
	cpu_switch_to(prev, next);
}

void _schedule()
{
	/*
	 * Preemption is disabled for the current task.
	 * We don't want to be rescheduled to a different task
	 * in the middle of the scheduling function.
	 */
	preempt_disable();

	int next, c;
	task_struct *p;

	/*
	 * Endless loop that we exit, only if a task to be rescheduled is found
	 */
	while(1) {
		c = -1;
		next = 0;
		/*
		 * Iterate over all tasks and try to find a running task,
		 * with the maximum counter.
		 */
		for (size_t i = 0; i < NR_TASKS; i++) {
			p = task[i];

			if (i <= 2) {
				printk("--- DEBUG: 1st for loop, checking Task %d, counter = %d, c = %d\n", i, p->counter, c);
			}

			/* If such a running task is found */
			if (p && p->state == TASK_RUNNING && p->counter > c) {
				/* Update maximum counter, and pid for next task */
				c = p->counter;
				next = i;
				printk("--- DEBUG: 1st for loop, FOUND Task %d, counter = %d, c = %d\n", i, p->counter, c);
			}
		}
		/* If a task to be scheduled is found, break and switch to task */
		/* Its counter is greater then 0 (c > 0) ?? */
		if (c) {
			printk("--- DEBUG: Breaking scheduler with, Task %d, c = %d\n", next, c);
			break;
		}
		/*
		 * If no such task is found, this means that:
		 * - No tasks in TASK_RUNNING state currently exist
		 * - Or all such tasks have 0 counters
		 * No matter what state the task are, increase its counter
		 */
		for (size_t i = 0; i < NR_TASKS; i++) {
			p = task[i];
			if (i <= 2) {
				printk("--- DEBUG: 2nd for loop, checking Task %d, counter = %d\n", i, p->counter);
			}
			/* p > 0 */
			if (p) {
				/*
				 * The more iterations of the 2nd loop a task
				 * passes, the more its counter will be increased.
				 * A task counter can never get larger
				 * than 2*priority.
				 */
				p->counter = (p->counter >> 1) + p->priority;
				/* (p->counter >> 1) = p->counter/2 */
			}
		}
	}
	printk("--- DEBUG: Selected for scheduling task %d, located in %d\n", next, task[next]);
	// printk("\nSelected for scheduling task %d, located in %d\n", next, task[next]);
	/* Finally we switch to the selected task */
	switch_to(task[next]);
	/* Re-enable preemption at end of function */
	printk("--- DEBUG: Succesfully did context switch with task %d, located in %d\n", next, task[next]);
	preempt_enable();
}

void schedule()
{
	printk("\n--- DEBUG: schedule() call, in Task located in %d, with counter = %d\n", current, current->counter);
	/* Set current task as reschedulable */
	current->counter = 0;
	/* Call, core scheduler function */
	_schedule();
}

void timer_tick()
{
	printk("\n--- DEBUG: timer_tick() call, in Task located in, with counter = %d\n", current, current->counter);
	/* Decreases current's task counter */
	--current->counter;
	/* Check if task has time left or preemption is disabled */
	if (current->counter > 0 || current->preempt_count > 0) {
		/* Then, can not reschedule task, exit */
		return;
	}
	/* Else, task can be rescheduled */
	current->counter = 0;	/* Reset reschedule counter */
	/*
	 *Enable interrupts for scheduler.
	 * We are inside an interrupt handler, and IRQs are disabled by default
	 */
	irq_enable();
	_schedule();		/* Call scheduler */
	irq_disable();		/* Disable interrupts */
}