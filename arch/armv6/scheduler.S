/*
 * scheduler.S - Implementation of armv6 scheduler helper functions.
 */

#include <armv6/scheduler.h>

.globl ret_from_fork
ret_from_fork:
	/* A call to preempt_enable(), in order for the task to be rescheduled */
	bl schedule_tail
	/*
	 * Calls the process function stored in r4,
	 * with the argument stored in r5.
	 * (Registers convention set by fork.c)
	 */
	mov r0, r5
	mov lr, r4
	blx lr 		/* Should never return */

/*
 * Gets called by scheduler() in order to perform the context switch.
 * Arguments:
 * - r0: Pointer to the task_struct of the task we are switching.
		(Starting address of memory page of the new task).
 * - r1: Pointer to the next task_struct
 */
.globl cpu_switch_to
cpu_switch_to:
	/* Get offset of cpu_context from task_struct */
	mov r12, #THREAD_CPU_CONTEXT
	/*
	 * Calculate the pointer to the cpu_context struct of current task
	 * r12: Points to the cpu_context of current task
	 */
	add r12, r0, r12	/* r12 = &task_struct + THREAD_CPU_CONTEXT */
	/* Save current stack pointer of current task */
	push {sp}
	/*
	 * All calle-saved registers are stored in the order
	 * they are defined in cpu_context structure.
	 */
	str r0,  [r12], #4
	str r1,  [r12], #4
	str r2,  [r12], #4
	str r3,  [r12], #4
	str r4,  [r12], #4
	str r5,  [r12], #4
	str r6,  [r12], #4
	str r7,  [r12], #4
	str r8,  [r12], #4
	str r9,  [r12], #4
	str r10, [r12], #4
	str r11, [r12], #4
	/* Save current stack pointer sp */
	pop {r11}
	str r11, [r12], #4
	/* Save cpsr */
	mrs r11, cpsr
	str r11, [r12], #4
	/* Save lr as pc */
	str lr,  [r12]

	/*
	 * Calculate the pointer to the next cpu_context struct
	 * r12: Points to the cpu_context of the next task
	 */
	mov r12, #THREAD_CPU_CONTEXT
	add r12, r1, r12	/* r12 = &(task_struct + 1) + THREAD_CPU_CONTEXT */
	/*
	 * All calle-saved registers are restored in the order
	 * they are defined in cpu_context structure.
	 * Callee saved registers are restored from the next cpu_context.
	 */
	ldr r0,  [r12], #4
	ldr r1,  [r12], #4
	ldr r2,  [r12], #4
	ldr r3,  [r12], #4
	ldr r4,  [r12], #4
	ldr r5,  [r12], #4
	ldr r6,  [r12], #4
	ldr r7,  [r12], #4
	ldr r8,  [r12], #4
	ldr r9,  [r12], #4
	ldr r10, [r12], #4
	ldr r11, [r12], #4
	/* Restore stack pointer sp */
	ldr sp,  [r12], #4
	/* Restore cpsr */
	push {r11}
	ldr r11, [r12], #4
	msr cpsr_c, r11
	pop {r11}
	/* Restore pc, by saving to lr and branching */
	ldr lr,  [r12]
	blx lr
