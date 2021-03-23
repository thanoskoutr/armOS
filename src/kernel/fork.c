/**
 * @file fork.c
 * @brief Implementation of fork-related functions.
 */

#include <stdint.h>

#include <kernel/fork.h>
#include <kernel/scheduler.h>
#include <kernel/mm.h>
#include <kernel/printk.h>

#ifdef AARCH_32
#elif AARCH_64
#include <armv8-a/utils.h>
#endif

#ifdef AARCH_32
int copy_process(uint32_t clone_flags, uint32_t fn, uint32_t arg, uint32_t stack)
#elif AARCH_64
int copy_process(uint64_t clone_flags, uint64_t fn, uint64_t arg, uint64_t stack)
#endif
{
	/*
	 * Preemption is disabled for the current task.
	 * We don't want to be rescheduled to a different task
	 * in the middle of the copy_process function.
	*/
	preempt_disable();
	/* Allocate pointer for the new task */
	task_struct *p;

	/* Allocate a page for the new task */
	p = (task_struct *) get_free_page();
	/* If there are no available pages, return with error */
	if (p == 0) {
		return -1;
	}

	pt_regs *childregs = task_pt_regs(p);
#ifdef AARCH_32
	memzero((uint32_t) childregs, sizeof(pt_regs));
	memzero((uint32_t) &p->cpu_context, sizeof(cpu_context));
#elif AARCH_64
	memzero((uint64_t) childregs, sizeof(pt_regs));
	memzero((uint64_t) &p->cpu_context, sizeof(cpu_context));
#endif

	if (clone_flags & PF_KTHREAD) {
#ifdef AARCH_32
		/*
		 * r4: The function to call for the new task
		 * r5: The argument for the function of the new task
		 */
		p->cpu_context.r4 = fn;
		p->cpu_context.r5 = arg;
#elif AARCH_64
		/*
		 * x19: The function to call for the new task
		 * x20: The argument for the function of the new task
		 */
		p->cpu_context.x19 = fn;
		p->cpu_context.x20 = arg;
#endif
	}
	else {
		pt_regs *cur_regs = task_pt_regs(current);
		*childregs = *cur_regs;
		childregs->regs[0] = 0;
		childregs->sp = stack + PAGE_SIZE;
		p->stack = stack;
	}

	/*
	 * p points to the starting address of the allocated page
	 * At the bottom of this page, we place the task_struct for the new task
	 * The rest of this page, will be used as the stack of the new task
	 */
	p->flags = clone_flags;
	p->state = TASK_RUNNING;
	p->priority = current->priority; /* Based on current task priority */
	p->counter = p->priority;	 /* Based on current task priority */
	p->preempt_count = 1;		 /* Should not be rescheduled */

#ifdef AARCH_32
	/* Initialize the cpu_context of the new task
	* pc: Points to the starting point for each new task (in asm)
	* sp: The stack pointer is set to the top of the newly allocated memory page
	* cpsr: Stay in supervisor mode (mode 0x13),
	*	IRQs enabled on process start (bit 7 = 0)
	*	Set bit 8 to disable a kind of exception that we are not using.
	*/
	p->cpu_context.pc = (uint32_t) ret_from_fork;
	p->cpu_context.sp = (uint32_t) childregs;
	p->cpu_context.cpsr = 0x13 | (8 << 1);
#elif AARCH_64
	/* Initialize the cpu_context of the new task
	* pc: Points to the starting point for each new task (in asm)
	* sp: The stack pointer is set to the top of the newly allocated memory page
	*/
	p->cpu_context.pc = (uint64_t) ret_from_fork;
	p->cpu_context.sp = (uint64_t) childregs;
#endif
	/* Add newly created task to the task array */
	int pid = nr_tasks++;
	task[pid] = p;

	/* Enable preemption for the current task (fork) */
	preempt_enable();

	return pid;
}

pt_regs *task_pt_regs(task_struct *tsk)
{
	/*
	 * Calculates pt_regs location:
	 * task_struct location + size of task - size of pt_regs
	*/
#ifdef AARCH_32
	uint32_t p = (uint32_t) tsk + THREAD_SIZE - sizeof(pt_regs);
#elif AARCH_64
	uint64_t p = (uint64_t) tsk + THREAD_SIZE - sizeof(pt_regs);
#endif
	return (pt_regs *) p;
}

#ifdef AARCH_32
int move_to_user_mode(uint32_t pc)
#elif AARCH_64
int move_to_user_mode(uint64_t pc)
#endif
{
	/* Get pt_regs address of current task */
	pt_regs *regs = task_pt_regs(current);

	/* Zero out the pt_regs section */
#ifdef AARCH_32
	memzero((uint32_t) regs, sizeof(*regs));
#elif AARCH_64
	memzero((uint64_t) regs, sizeof(*regs));
#endif
	/*
	 * Prepare processor state with the format that the kernel_exit macro expects.
	 * - pc: It now points to the function that needs to be executed in the user mode.
	 * kernel_exit will copy pc to the elr_el1 register, thus making sure
	 * that we will return to the pc address after performing exception return.
	 * - pstate: This field will be copied to spsr_el1 by the kernel_exit
	 * and becomes the processor state after exception return is completed.
	 * PSR_MODE_EL0t constant, which is copied to the pstate field,
	 * is prepared in such a way that exception return will be made to EL0 level.
	 * - stack: move_to_user_mode allocates a new page for the user stack
	 * and sets sp field to point to the top of this page.
	 */
	regs->pc = pc;
	regs->pstate = PSR_MODE_EL0t;
#ifdef AARCH_32
	uint32_t stack = get_free_page(); /* Allocate new user stack */
#elif AARCH_64
	uint64_t stack = get_free_page(); /* Allocate new user stack */
#endif
	if (stack == 0) {
		/* Could not allocate page */
		return -1;
	}
	regs->sp = stack + PAGE_SIZE;

	current->stack = stack;

	return 0;
}