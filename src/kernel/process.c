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


void init_processes(size_t proc_num)
{
	/* String array, for the message of each process */
	static char args[NR_TASKS][MAX_INPUT_LENGTH];

	for (size_t i = 0; i < proc_num; i++) {
		printk("Forking process %d...", i);

		strcpy(args[i], "Hello from proc ");
		strcat(args[i], itoa(i));
		strcat(args[i], ", ");

#ifdef AARCH_32
		// int res = copy_process((uint32_t) &process, (uint32_t) "12345");
		int res = copy_process((uint32_t) &process, (uint32_t) args[i]);
#elif AARCH_64
		// int res = copy_process((uint64_t) &process, (uint64_t) "12345");
		int res = copy_process((uint64_t) &process, (uint64_t) args[i]);
#endif
		if (res != 0) {
			printk("Error while starting process 1\n");
			return;
		}
		printk("Done\n");
	}
}
