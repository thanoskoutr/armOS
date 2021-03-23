/*
 * entry.S - Implementation of armv8-a exception vectors.
 */

#include <armv8-a/entry.h>
#include <armv8-a/sysregs.h>
#include <armv8-a/sys.h>

/*
 * Macro for creating entries in the vector table.
 * Jump to the label that is provided for the macro as label argument.
 * All except. vectors should be located at offset 0x80 bytes one from another.
 */
.macro ventry label
.align 7
	b \label
.endm

/*
 * Macro for storing registers x0 - x30 to the stack, at the start of an
 * interrupt.
 */
	/* stp: Stores a pair of registers */
.macro kernel_entry, el
	sub sp,  sp,  #S_FRAME_SIZE
	stp x0,  x1,  [sp, #16 * 0]
	stp x2,  x3,  [sp, #16 * 1]
	stp x4,  x5,  [sp, #16 * 2]
	stp x6,  x7,  [sp, #16 * 3]
	stp x8,  x9,  [sp, #16 * 4]
	stp x10, x11, [sp, #16 * 5]
	stp x12, x13, [sp, #16 * 6]
	stp x14, x15, [sp, #16 * 7]
	stp x16, x17, [sp, #16 * 8]
	stp x18, x19, [sp, #16 * 9]
	stp x20, x21, [sp, #16 * 10]
	stp x22, x23, [sp, #16 * 11]
	stp x24, x25, [sp, #16 * 12]
	stp x26, x27, [sp, #16 * 13]
	stp x28, x29, [sp, #16 * 14]

	/*
	 * We are using 2 distinct stack pointers for EL0 and EL1.
	 * After an exception is taken from EL0 the stack pointer is overwritten.
	 * The original stack pointer can be found in the sp_el0 register.
	 * So the value of this register must be stored and restored before
	 * and after taking an exception.
	 */
	.if \el == 0
	mrs x21, sp_el0			/* Save sp_el0 to x21. */
	.else
	add x21, sp, #S_FRAME_SIZE	/* Size of all saved registers. */
	.endif 				/* \el == 0 */

	/*
	 * Because of context switching, it is possible to enter the interrupt
	 * as one task, and exit as a different one.
	 * eret, relies on the fact that return address is stored in elr_el1
	 * and processor state in spsr_el1.
	 * In order to switch tasks while processing an interrupt, we must save
	 * these 2 registers, alongside the other general purpose registers.
	 */
	mrs x22, elr_el1
	mrs x23, spsr_el1

	stp x30, x21, [sp, #16 * 15]
	stp x22, x23, [sp, #16 * 16]
.endm

/*
 * Macro for restoring the processor state by copying back the values of
 * x0 - x30 registers at the end of an interrupt.
 */
	/* ldp: Loads a pair of registers */
.macro kernel_exit, el

	ldp x22, x23, [sp, #16 * 16]
	ldp x30, x21, [sp, #16 * 15]

	/*
	 * Because we use both EL0 and EL1 states, we do the opposite from kernel_entry.
	 * We firts restore sp_el0, before restoring the other
	 * general purpose registers.
	 */
	.if \el == 0
	msr sp_el0, x21
	.endif			/* \el == 0 */

	/*
	 * Because of context switching, we do the opposite from kernel_entry.
	 * We restore elr_el1 and spsr_el1, before restoring the other
	 * general purpose registers.
	 */
	msr elr_el1, x22
	msr spsr_el1, x23

	ldp x0,  x1,  [sp, #16 * 0]
	ldp x2,  x3,  [sp, #16 * 1]
	ldp x4,  x5,  [sp, #16 * 2]
	ldp x6,  x7,  [sp, #16 * 3]
	ldp x8,  x9,  [sp, #16 * 4]
	ldp x10, x11, [sp, #16 * 5]
	ldp x12, x13, [sp, #16 * 6]
	ldp x14, x15, [sp, #16 * 7]
	ldp x16, x17, [sp, #16 * 8]
	ldp x18, x19, [sp, #16 * 9]
	ldp x20, x21, [sp, #16 * 10]
	ldp x22, x23, [sp, #16 * 11]
	ldp x24, x25, [sp, #16 * 12]
	ldp x26, x27, [sp, #16 * 13]
	ldp x28, x29, [sp, #16 * 14]
	add sp, sp, #S_FRAME_SIZE
	eret
.endm


/*
 * Macro for handlers that should never be executed in normal flow.
 * We call the C function show_invalid_entry_message, in order to print
 * information about the error, and the processor is put in an infinite loop.
 *
 * \el:     Indicates which exception level an exception is taken from.
 *		The information about the originating exception level
 *		is required to properly save/restore stack pointer.
 * #\type:  Invalid type defined in <armv8-a/entry.h>
 * esr_el1: Exception Syndrome Register (ESR) contains detailed information
 *		about what causes an exception.
 * elr_el1: Exception Link Register (ELR) contains the address of the
 *		instruction that had been executed when the exception
 *		was generated (for synchronous interrupts).
 */
.macro handle_invalid_entry el, type
	kernel_entry \el
	mov x0, #\type
	mrs x1, esr_el1
	mrs x2, elr_el1
	bl show_invalid_entry_message
	b err_hang
.endm


/*
 * Exception vector table.
 * 16 entries created with the ventry macro.
 * For each exception we jump to the corresponding label (handler).
 */
.align 11
.globl vectors
vectors:
	ventry sync_invalid_el1t	/* Synchronous EL1t */
	ventry irq_invalid_el1t		/* IRQ EL1t         */
	ventry fiq_invalid_el1t		/* FIQ EL1t         */
	ventry error_invalid_el1t	/* Error EL1t       */

	ventry sync_invalid_el1h	/* Synchronous EL1h */
	ventry el1_irq			/* IRQ EL1h         */
	ventry fiq_invalid_el1h		/* FIQ EL1h         */
	ventry error_invalid_el1h	/* Error EL1h       */

	ventry el0_sync			/* Synchronous 64-bit EL0 */
	ventry el0_irq			/* IRQ 64-bit EL0         */
	ventry fiq_invalid_el0_64	/* FIQ 64-bit EL0         */
	ventry error_invalid_el0_64	/* Error 64-bit EL0       */

	ventry sync_invalid_el0_32	/* Synchronous 32-bit EL0 */
	ventry irq_invalid_el0_32	/* IRQ 32-bit EL0         */
	ventry fiq_invalid_el0_32	/* FIQ 32-bit EL0         */
	ventry error_invalid_el0_32	/* Error 32-bit EL0       */

/*
 * Implementation of exception handlers.
 */

 /* For other exceptions: We call the handle_invalid_entry macro,
	with the corresponding invalid exception type value. */
sync_invalid_el1t:
	handle_invalid_entry 1, SYNC_INVALID_EL1t

irq_invalid_el1t:
	handle_invalid_entry 1, IRQ_INVALID_EL1t

fiq_invalid_el1t:
	handle_invalid_entry 1, FIQ_INVALID_EL1t

error_invalid_el1t:
	handle_invalid_entry 1, ERROR_INVALID_EL1t

sync_invalid_el1h:
	handle_invalid_entry 1, SYNC_INVALID_EL1h

fiq_invalid_el1h:
	handle_invalid_entry 1, FIQ_INVALID_EL1h

error_invalid_el1h:
	handle_invalid_entry 1, ERROR_INVALID_EL1h

fiq_invalid_el0_64:
	handle_invalid_entry 0, FIQ_INVALID_EL0_64

error_invalid_el0_64:
	handle_invalid_entry 0, ERROR_INVALID_EL0_64

sync_invalid_el0_32:
	handle_invalid_entry 0, SYNC_INVALID_EL0_32

irq_invalid_el0_32:
	handle_invalid_entry 0, IRQ_INVALID_EL0_32

fiq_invalid_el0_32:
	handle_invalid_entry 0, FIQ_INVALID_EL0_32

error_invalid_el0_32:
	handle_invalid_entry 0, ERROR_INVALID_EL0_32

/* For IRQ EL1h: We call the exception handler handle_irq from C code. */
el1_irq:
	kernel_entry 1
	bl handle_irq
	kernel_exit 1

/* For IRQ 64-bit EL0: We call the exception handler handle_irq from C code. */
el0_irq:
	kernel_entry 0
	bl handle_irq
	kernel_exit 0

/* For Synchronous 64-bit EL0: Gets generated by the syscall wrappers. */
el0_sync:
	kernel_entry 0
	/* Check Exception Syndrome Register (esr_el1). */
	mrs x25, esr_el1
	/* Contains "exception class" field at offset ESR_ELx_EC_SHIFT. */
	lsr x24, x25, #ESR_ELx_EC_SHIFT
	/*
	 * If exception class is equal to ESR_ELx_EC_SVC64 this means that
	 * the current exception is caused by the svc instruction
	 * and it is a system call.
	 */
	cmp x24, #ESR_ELx_EC_SVC64
	/* If it is, jump to el0_svc label to execute the syscall handler. */
	b.eq el0_svc
	/* Else, call the exception handler from C code to show error message */
	handle_invalid_entry 0, SYNC_ERROR


/*
 * Aliases of some registers, based on their use.
 */
sc_nr	.req	x25	/* Number of system calls */
scno	.req	x26	/* Syscall number */
stbl	.req	x27	/* Syscall table pointer */

/* Handler for valid Synchronous 64-bit EL0 */
el0_svc:
	adr stbl, sys_call_table	/* Load syscall table address */
	/* uxtw: extends 32-bit w8 to 64-bit x8 */
	uxtw scno, w8			/* Load syscall number in w8 */
	mov sc_nr, #__NR_syscalls	/* Load total number of syscalls */
	bl irq_enable			/* Enable interrupts */
	cmp scno, sc_nr			/* Check upper syscall limit */
	b.hs ni_sys			/* If scno >= __NR_syscalls, print error */

	/* Else, if syscall number is valid, it is used as an index the syscall table array */
	ldr x16, [stbl, scno, lsl #3]	/* Obtain the address of the syscall from the syscall table */
	blr x16				/* Call sys_* routine */
	b ret_from_syscall		/* Branch after return from syscall */

/* Calls the handle_invalid_entry macro, with the corresponding error value. */
ni_sys:
	handle_invalid_entry 0, SYSCALL_ERROR

/*
 * Clean-up function, after every syscall.
 * - Disables IRQs
 * - Saves return value of syscall (in x0 reg) on the stack, because kernel_exit
 *	will restore all registers, including x0, and we will lose return value.
 * - Execute kernel_exit, in order to restore registers from EL0 state.
 */
ret_from_syscall:
	bl irq_disable			/* Disables interrupts */
	str x0, [sp, #S_X0]		/* Saves value of x0 in the stack */
	kernel_exit 0			/* Restore EL0 state */


/*
 * Starting point for each new task.
 *  PC register of each new task points here.
 */
.globl ret_from_fork
ret_from_fork:
	/* A call to preempt_enable(), in order for the task to be rescheduled */
	bl schedule_tail
	/* If x19 == 0, it is a kernel_thread, branch to ret_to_user */
	cbz x19, ret_to_user
	/*
	 * Calls the process function stored in x19,
	 * with the argument stored in x20.
	 * (Registers convention set by fork.c)
	 */
	mov x0, x20
	blr x19 	/* Should never return */
/*
 * We disable interrupts and perform normal exception return,
 * using previously prepared processor state
 */
ret_to_user:
	bl irq_disable
	kernel_exit 0


/*
 * Function for putting the processor in an infinite loop, in case of error.
 */
.globl err_hang
err_hang:
	b err_hang