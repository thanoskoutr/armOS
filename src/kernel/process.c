/*
 * process.c - Creates processes.
 */


#include <stdint.h>

#include <kernel/printk.h>
#include <kernel/mmio.h>
#include <kernel/timer.h>
#include <kernel/fork.h>
#include <kernel/scheduler.h>


/*
 * Dummy function that simulated a process.
 * It just prints the items of its array.
 */
void process(char *array)
{
	while (1) {
		for (int i = 0; i < 5; i++) {
			printk("%c", array[i]);
			delay(100000);
		}
	}
}


void init_processes()
{
	/* Creates process 1 */
	printk("Forking process 1...");
#ifdef AARCH_32
	int res = copy_process((uint32_t) &process, (uint32_t) "12345");
#elif AARCH_64
	int res = copy_process((uint64_t) &process, (uint64_t) "12345");
#endif
	if (res != 0) {
		printk("Error while starting process 1\n");
		return;
	}
	printk("Done\n");

	/* Creates process 2 */
	printk("Forking process 2...");
#ifdef AARCH_32
	res = copy_process((uint32_t) &process, (uint32_t) "abcde");
#elif AARCH_64
	res = copy_process((uint64_t) &process, (uint64_t) "abcde");
#endif
	if (res != 0) {
		printk("Error while starting process 2\n");
		return;
	}
	printk("Done\n");

	/* Creates process 3 */
	printk("Forking process 3...");
#ifdef AARCH_32
	res = copy_process((uint32_t) &process, (uint32_t) "!@#$^");
#elif AARCH_64
	res = copy_process((uint64_t) &process, (uint64_t) "!@#$^");
#endif
	if (res != 0) {
		printk("Error while starting process 3\n");
		return;
	}
	printk("Done\n");
}