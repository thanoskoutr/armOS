/*
 * scheduler.S - Implementation of armv8-a scheduler helper functions.
 */

#include <armv8-a/scheduler.h>

.globl ret_from_fork
ret_from_fork:
	/* A call to preempt_enable(), in order for the task to be rescheduled */
	bl schedule_tail
	/*
	 * Calls the process function stored in x19,
	 * with the argument stored in x20.
	 * (Registers convention set by fork.c)
	 */
	mov x0, x20
	blr x19 	/* Should never return */

/*
 * Gets called by scheduler() in order to perform the context switch.
 * Arguments:
 * - x0: Pointer to the task_struct of the task we are switching.
		(Starting address of memory page of the new task).
 * - x1: Pointer to the next task_struct
 */
.globl cpu_switch_to
cpu_switch_to:
	/* Get offset of cpu_context from task_struct */
	mov x10, #THREAD_CPU_CONTEXT
	/*
	 * Calculate the pointer to the cpu_context struct of current task
	 * x8: Points to the cpu_context of current task
	 */
	add x8, x0, x10		/* x8 = &task_struct + THREAD_CPU_CONTEXT */
	/* Save current stack pointer of current task */
	mov x9, sp
	/*
	 * All calle-saved registers are stored in the order
	 * they are defined in cpu_context structure.
	 */
	stp x19, x20, [x8], #16
	stp x21, x22, [x8], #16
	stp x23, x24, [x8], #16
	stp x25, x26, [x8], #16
	stp x27, x28, [x8], #16
	/* x29 is saved as fp (frame pointer) */
	/* current stack pointer is saved as sp */
	stp x29, x9,  [x8], #16
	/* x30 (link register that contains function return address), is stored as pc */
	str x30,      [x8]
	/*
	 * Calculate the pointer to the next cpu_context struct
	 * x8: Points to the cpu_context of the next task
	 */
	add x8, x1, x10		/* x8 = &(task_struct + 1) + THREAD_CPU_CONTEXT */
	/*
	 * All calle-saved registers are restored in the order
	 * they are defined in cpu_context structure.
	 * Callee saved registers are restored from the next cpu_context.
	 */
	ldp x19, x20, [x8], #16
	ldp x21, x22, [x8], #16
	ldp x23, x24, [x8], #16
	ldp x25, x26, [x8], #16
	ldp x27, x28, [x8], #16
	ldp x29, x9,  [x8], #16
	ldr x30,      [x8]
	mov sp, x9
	/*
	 * Function returns to the location pointed to by the link register (x30):
	 * - If we are switching to some task for the first time, this will be
	 * 	ret_from_work
	 * - Else, this will be the location, previously saved in the
	 * 	cpu_context by the cpu_switch_to function
	 */
	ret


