/**
 * \ingroup processes
 * @file process.h
 * @brief Definition of functions for creating and killing processes.
 */

#ifndef PROCESS_H
#define PROCESS_H

#include <stddef.h>

/**
 * \ingroup processes
 * Creates processes using @ref copy_process().
 * @param proc_num Number of processes to fork.
 * @details Maximum number of processes that can be created is @ref NR_TASKS.
 * @see copy_process(), NR_TASKS, task_struct
 */
void create_processes(size_t proc_num);


/**
 * \ingroup processes
 * Kills all running processes (except `init_task`).
 * @details Do for each process:
 * - Get starting address of process.
 * - Check that it is not the current process (`init_task`).
 * - Free page.
 * - Decrease number of processes (Decrease @ref nr_tasks).
 * - Remove @ref task_struct from @ref task array (Set `task[pid] = 0`).
 *
 * @see free_page(), preempt_disable(), task_struct
 */
void kill_processes();

#endif