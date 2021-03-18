/*
 * process.c - Creates processes.
 */


#include <stdint.h>
#include <stddef.h>

#include <kernel/printk.h>
#include <kernel/mmio.h>
#include <kernel/timer.h>
#include <kernel/fork.h>
#include <kernel/scheduler.h>
#include <kernel/uart.h>

#include <common/string.h>
#include <common/stdlib.h>

/* String array, for the message of each process */
static char proc_args[NR_TASKS][MAX_INPUT_LENGTH];

/*
 * Dummy function that simulated a process.
 * It just prints the items of its array.
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
		// int res = copy_process((uint32_t) &process, (uint32_t) "12345");
		int res = copy_process((uint32_t) &process, (uint32_t) proc_args[pid]);
#elif AARCH_64
		// int res = copy_process((uint64_t) &process, (uint64_t) "12345");
		int res = copy_process((uint64_t) &process, (uint64_t) proc_args[pid]);
#endif
		if (res != 0) {
			printk("Error while starting process %d\n", pid);
			return;
		}
		printk("Done\n");
	}
}
