/*
 * scheduler.h - Definition of scheduler structs and functions
 */

#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <stdint.h>

/*
 * Structure that contains values of all registers that might be different
 * between the tasks, that are being switched.
 * We don't save registers x0 - x18 becuase they can be overwritten
 * by the called function, so the caller must not assume that the values
 * of those registers will survive after a function call
 */
#ifdef AARCH_32
typedef struct _cpu_context {
	uint32_t r0;
	uint32_t r1;
	uint32_t r2;
	uint32_t r3;
	uint32_t r4;
	uint32_t r5;
	uint32_t r6;
	uint32_t r7;
	uint32_t r8;
	uint32_t r9;
	uint32_t r10;
	uint32_t r11;
	uint32_t sp;
	uint32_t cpsr;
	uint32_t pc;

} cpu_context;
#elif AARCH_64
typedef struct _cpu_context {
	uint64_t x19;
	uint64_t x20;
	uint64_t x21;
	uint64_t x22;
	uint64_t x23;
	uint64_t x24;
	uint64_t x25;
	uint64_t x26;
	uint64_t x27;
	uint64_t x28;
	uint64_t fp;
	uint64_t sp;
	uint64_t pc;
} cpu_context;
#endif

/*
 * Structure that describes a process.
 * This struct has the following members:
 * - cpu_context: A struct for the registers to be saved for the process.
 * - state: The state of the currently running task.
 * - counter: Used to determine how long the current task has been running.
 * Decreases by 1 each timer tick. When it reaches 0 another task is scheduled.
 * - priority: When a new task is scheduled its priority is copied to counter.
 * We regulate the amount of cpu time the task gets relative to other tasks.
 * - preempt_count: Non-zero value indicates critical task, that must not be
 * 			interrupted.
 */
#ifdef AARCH_32
typedef struct _task_struct {
	cpu_context cpu_context;
	int32_t state;
	int32_t counter;
	int32_t priority;
	int32_t preempt_count;
} task_struct;
#elif AARCH_64
typedef struct _task_struct {
	cpu_context cpu_context;
	int64_t state;
	int64_t counter;
	int64_t priority;
	int64_t preempt_count;
} task_struct;
#endif

/*
 * Task States
 */
#define TASK_RUNNING 0
/*
 * Maximum number of concurrent tasks
 */
#define NR_TASKS 64

/*
 * task[NR_TASKS]:	Array that holds all the tasks
 * current:		Pointer that points to the currently executing task
 * nr_tasks:		Number of currently running tasks
 */
extern task_struct *task[NR_TASKS];
extern task_struct *current;
extern int nr_tasks;

/*
 * Defines for first and last task
 */
#define FIRST_TASK task[0]
#define LAST_TASK task[NR_TASKS-1]

/*
 * Defines size of each process == Page Size
 */
#define THREAD_SIZE 4096

/*
 * Defines the init task's task_struct (kernel_main) that is run on kernel startup
 * - cpu_context: All registers initialized to 0.
 * - state = 0 (TASK_RUNNING)
 * - counter = 0
 * - priority = 1
 * - preempt_count = 0 (can be rescheduled)
 */
#ifdef AARCH_32
#define INIT_TASK \
/*cpu_context*/	{ {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, \
/* state etc */	0,0,1,0 \
}
#elif AARCH_64
#define INIT_TASK \
/*cpu_context*/	{ {0,0,0,0,0,0,0,0,0,0,0,0,0}, \
/* state etc */	0,0,1,0 \
}
#endif


/* scheduler.S
 * Starting point for each new task (pc reg. of each new task points here)
 */
void ret_from_fork();

/* scheduler.S
 * Performs the context switch, by changing the registers.
 */
extern void cpu_switch_to(task_struct *prev, task_struct *next);

/*
 * Enables/Disables preemption for the current running task
 */
extern void preempt_disable();
extern void preempt_enable();

/*
 * First function that gets called from a new task, that calls preempt_enable()
 * after its initialization, in order for the task to be rescheduled.
 */
extern void schedule_tail();

/*
 * Function that switches from current to the next task.
 * Calls cpu_next_to, in order to perform the necessary context switch.
 */
extern void switch_to(task_struct* next);

/*
 * Wrapper for core scheduler function _schedule().
 * Checks whether there is a new task, that needs to preempt the current one.
 * Gets called:
 * - Explicitly by another task.
 * - From timer interrupt handler.
 */
extern void schedule();

/*
 * Calls schedule after a time interval.
 * Gets called from timer interrupt handler.
 */
extern void timer_tick();


#endif