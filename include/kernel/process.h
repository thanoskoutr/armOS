/*
 * process.h - Definition of function for creating processes.
 */

#ifndef PROCESS_H
#define PROCESS_H

#include <stddef.h>

/*
 * Creates processes using copy_process.
 */
void init_processes(size_t proc_num);


/*
 * Run:
 * - If init_processes() is before console(): At halt.
 * - If init_processes() is in cmd_process: On end of cmd_process
 * Must do for each process:
 * - Get starting address of process
 * - Check that it is not current process
 * - Free page
 * - Decrease number of processes (nr_tasks--)
 * - Remove task_struct from task array (task[pid] = 0)
 */
void kill_processes();

#endif