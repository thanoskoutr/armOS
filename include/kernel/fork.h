/*
 * fork.h - Definition of fork-related functions.
 */

#ifndef FORK_H
#define FORK_H

#include <stdint.h>

/*
 * Functions for creating a new process.
 * Allocates a new task_struct and makes it available for the scheduler.
 * @fn: A function to execute in a new thread
 * @arg: An argument that need to be passed to this function
 * Returns:
 * - On success: 0
 * - On failure: 1
 */
#ifdef AARCH_32
int copy_process(uint32_t fn, uint32_t arg);
#elif AARCH_64
int copy_process(uint64_t fn, uint64_t arg);
#endif

#endif