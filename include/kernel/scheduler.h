/**
 * @file scheduler.h
 * @brief Definition of scheduler structs and functions.
 */

#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <stdint.h>

/**
 * Structure that contains values of all registers that might be different
 * between the tasks, that are being switched.
 * @note For **aarch64**: We don't save registers `x0 - x18` becuase they can be overwritten
 * by the called function, so the caller must not assume that the values
 * of those registers will survive after a function call. \n
 * For **aarch32**: We don't save register `r12`  because it is a caller-save
 * register, so its value need not be preserved.
 */
#ifdef AARCH_32
typedef struct _cpu_context {
	uint32_t r0;   /**< Unbanked register R0 */
	uint32_t r1;   /**< Unbanked register R1 */
	uint32_t r2;   /**< Unbanked register R2 */
	uint32_t r3;   /**< Unbanked register R3 */
	uint32_t r4;   /**< Unbanked register R4 */
	uint32_t r5;   /**< Unbanked register R5 */
	uint32_t r6;   /**< Unbanked register R6 */
	uint32_t r7;   /**< Unbanked register R7 */
	uint32_t r8;   /**< Unbanked register R8 (Except FIQ) */
	uint32_t r9;   /**< Unbanked register R9 (Except FIQ) */
	uint32_t r10;  /**< Unbanked register R10 (Except FIQ) */
	uint32_t r11;  /**< Unbanked register R11 (Except FIQ) */
	uint32_t sp;   /**< Stack Pointer (R13) */
	uint32_t cpsr; /**< Current Program Status Register */
	uint32_t pc;   /**< Program Counter (R15) */

} cpu_context;
#elif AARCH_64
typedef struct _cpu_context {
	uint64_t x19; /**< General Purpose 64-bit register X19 (Callee-saved) */
	uint64_t x20; /**< General Purpose 64-bit register X20 (Callee-saved) */
	uint64_t x21; /**< General Purpose 64-bit register X21 (Callee-saved) */
	uint64_t x22; /**< General Purpose 64-bit register X22 (Callee-saved) */
	uint64_t x23; /**< General Purpose 64-bit register X23 (Callee-saved) */
	uint64_t x24; /**< General Purpose 64-bit register X24 (Callee-saved) */
	uint64_t x25; /**< General Purpose 64-bit register X25 (Callee-saved) */
	uint64_t x26; /**< General Purpose 64-bit register X26 (Callee-saved) */
	uint64_t x27; /**< General Purpose 64-bit register X27 (Callee-saved) */
	uint64_t x28; /**< General Purpose 64-bit register X28 (Callee-saved) */
	uint64_t fp;  /**< Fram Pointer: 64-bit register X29 (Callee-saved) */
	uint64_t sp;  /**< Stack Pointer */
	uint64_t pc;  /**< Program Counter */
} cpu_context;
#endif

/**
 * Structure that describes a process.
 * @details This struct has the following members:
 * - task_struct.cpu_context: A struct for the registers to be saved for the process.
 * - task_struct.state: The state of the currently running task.
 * - task_struct.counter: Used to determine how long the current task has been running.
 * Decreases by 1 each timer tick. When it reaches 0 another task is scheduled.
 * - task_struct.priority: When a new task is scheduled its priority is copied to counter.
 * We regulate the amount of cpu time the task gets relative to other tasks.
 * - task_struct.preempt_count: Non-zero value indicates critical task, that must not be
 * 			interrupted.
 */
#ifdef AARCH_32
typedef struct _task_struct {
	cpu_context cpu_context; /**< A struct for the registers to be saved for the process. */
	int32_t state; /**< The state of the currently running task. */
	int32_t counter; /**< Used to determine how long the current task has been running. */
	int32_t priority; /**< When a new task is scheduled its priority is copied to counter. */
	int32_t preempt_count; /**< Non-zero value indicates critical task, that must not be interrupted. */
} task_struct;
#elif AARCH_64
typedef struct _task_struct {
	cpu_context cpu_context; /**< A struct for the registers to be saved for the process. */
	int64_t state; /**< The state of the currently running task. */
	int64_t counter; /**< Used to determine how long the current task has been running. */
	int64_t priority; /**< When a new task is scheduled its priority is copied to counter. */
	int64_t preempt_count; /**< Non-zero value indicates critical task, that must not be interrupted. */
} task_struct;
#endif

/**
 * Task States
 */
#define TASK_RUNNING 0
/**
 * Maximum number of concurrent tasks
 */
#define NR_TASKS 64


/** Array that holds all the tasks. */
extern task_struct *task[NR_TASKS];
/** Pointer that points to the currently executing task. */
extern task_struct *current;
/** Number of currently running tasks. */
extern int nr_tasks;

/**
 * Define the first task.
 * @see task
 */
#define FIRST_TASK task[0]
/**
 * Define the last task.
 * @see task
 */
#define LAST_TASK task[NR_TASKS-1]

/**
 * Defines size of each process.
 * @details Equal to the Page size ( @ref PAGE_SIZE).
 */
#define THREAD_SIZE 4096

/**
 * Defines the init task's @ref task_struct ( @ref kernel_main()) that is run on kernel startup.
 * @details Fields:
 * - cpu_context: All registers initialized to 0.
 * - state = 0 ( @ref TASK_RUNNING)
 * - counter = 0
 * - priority = 1
 * - preempt_count = 0 (can be rescheduled)
 *
 * @see task_struct, cpu_context, TASK_RUNNING
 */
#ifdef AARCH_32
#define INIT_TASK { /* cpu_context */ {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}, /* state etc */ 0,0,1,0 }
#elif AARCH_64
#define INIT_TASK { /*  cpu_context */ {0,0,0,0,0,0,0,0,0,0,0,0,0}, /* state etc */ 0,0,1,0 }
#endif


/**
 * Starting point for each new task.
 * @details PC register (cpu_context.pc) of each new task points here.
 * @see scheduler.S
 */
void ret_from_fork();

/**
 * Performs the context switch, by changing the registers.
 * @param prev Pointer to the @ref task_struct of the task we are switching
 * (Starting address of memory page of the new task).
 * @param next Pointer to the next @ref task_struct.
 * @see scheduler.S
 */
extern void cpu_switch_to(task_struct *prev, task_struct *next);

/**
 * Disables preemption for current running process.
 */
extern void preempt_disable();
/**
 * Enables preemption for current running process.
 */
extern void preempt_enable();

/**
 * Tail function that enables preemption for current process.
 * @details It is the last function a new task calls, after its initialization,
 *  in order for it to be rescheduled.
 * @see preempt_enable()
 */
extern void schedule_tail();

/**
 * Function that switches from current to the next task.
 * @param next A @ref task_struct pointer, that points to the next task.
 * @details Calls `cpu_next_to`, in order to perform the necessary context switch.
 * @see task_struct
 */
extern void switch_to(task_struct* next);

/**
 * Main scheduler function.
 * @details Wrapper for core scheduler function _schedule().
 * Checks whether there is a new task, that needs to preempt the current one. \n
 * Gets called:
 * - Explicitly by another task.
 * - From timer interrupt handler.
 *
 * @see switch_to(), task, preempt_disable(), preempt_enable()
 */
extern void schedule();

/**
 * Calls _schedule() after a time interval.
 * @details Gets called from System Timer interrupt handler.
 * @see handle_timer_3_irq(), _schedule()
 */
extern void timer_tick();


#endif