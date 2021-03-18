/*
 * process.h - Definition of function for creating processes.
 */

#ifndef PROCESS_H
#define PROCESS_H

#include <stddef.h>

/*
 * Creates processes using copy_process.
 */
void create_processes(size_t proc_num);


/*
 * Do for each process:
 * - Get starting address of process
 * - Check that it is not the current process (init)
 * - Free page
 * - Decrease number of processes (nr_tasks--)
 * - Remove task_struct from task array (task[pid] = 0)
 */
void kill_processes();

#endif