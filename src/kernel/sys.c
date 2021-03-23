/**
 * @file sys.c
 * @brief Implementation of syscall handlers.
 */

#include <kernel/printk.h>
#include <kernel/fork.h>
#include <kernel/mm.h>

void sys_write(char *buf)
{
	printk(buf);
}

int sys_clone(unsigned long stack)
{
	return copy_process(0, 0, 0, stack);
}

unsigned long sys_malloc()
{
	unsigned long addr = get_free_page();
	if (!addr) {
		return -1;
	}
	return addr;
}

void sys_exit()
{
	exit_process();
}


/**
 * Syscall Table
 * @details Declaration of syscall table.
 */
void * const sys_call_table[] = {sys_write, sys_malloc, sys_clone, sys_exit};