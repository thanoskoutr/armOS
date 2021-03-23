/**
 * @file process.c
 * @brief Implementation of functions for creating and killing processes.
 */


#include <stdint.h>
#include <stddef.h>

#include <kernel/printk.h>
#include <kernel/mmio.h>
#include <kernel/timer.h>
#include <kernel/fork.h>
#include <kernel/scheduler.h>
#include <kernel/uart.h>
#include <kernel/mm.h>

#include <common/string.h>
#include <common/stdlib.h>

/* String array, for the message of each process */
static char proc_args[NR_TASKS][MAX_INPUT_LENGTH];

/**
 * Dummy function that simulates a process.
 * @param array A char array pointer.
 * @details It just prints the items of its char array.
 */
void process(char *array)
{
	size_t items = strlen(array);
	while (1) {
		for (size_t i = 0; i < items; i++) {
			printk("%c", array[i]);
			delay(100000);
		}
	}
}


void create_processes(size_t proc_num)
{
	/* Get running tasks, for generating pid for each new task in the system */
	int pid = nr_tasks;
	int start_pid = nr_tasks;

	/* Create only a maximum of NR_TASKS */
	for (size_t i = 0; i < proc_num; i++, pid++) {

		/* Check if processes >= Maximum Total Processes */
		if (pid >= NR_TASKS) {
			printk("Can't create %d process(es)\n", proc_num - (pid - start_pid));
			printk("Total processes must be: 0 < procs < %d \n", NR_TASKS);
			return;
		}

		printk("Forking process %d...", pid);

		strcpy(proc_args[pid], "Hello from proc with pid = ");
		strcat(proc_args[pid], itoa(pid));
		strcat(proc_args[pid], ", ");

#ifdef AARCH_32
		// int res = copy_process((uint32_t) &process, (uint32_t) proc_args[pid]);
#elif AARCH_64
		// int res = copy_process((uint64_t) &process, (uint64_t) proc_args[pid]);
#endif
		// if (res != 0) {
			// printk("Error while starting process %d\n", pid);
			// return;
		// }
		printk("Done\n");
	}
}


void kill_processes()
{
	/*
	 * Preemption is disabled for the current task.
	 * We don't want to be rescheduled to a different task
	 * in the middle of killing another task.
	 */
	preempt_disable();

	/* Allocate pointer for the new task */
	task_struct *p;

	/*
	 * Iterate over all tasks and try to kill all runing ones.
	 */
	for (size_t i = 0; i < NR_TASKS; i++) {
		p = task[i];
		/* If it is an allocated task, and not the init task */
		if (p != 0 && i != 0) {
			/* Free allocated memory of task */
#ifdef AARCH_32
			free_page((uint32_t) p);
#elif AARCH_64
			free_page((uint64_t) p);
#endif
			/* Decrease number of processes */
			nr_tasks--;
			/* Remove task_struct from task array */
			task[i] = 0;

			printk("Killed task %d, located at %d\n", i, p);
		}
	}

}