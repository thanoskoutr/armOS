/*
 * entry.S - Implementation of armv6 exception vectors.
 */

#include <armv6/entry.h>

.section ".text"

/*
 * Macro for handlers that should never be executed in normal flow.
 * We call the C function show_invalid_entry_message, in order to print
 * information about the error, and the processor is put in an infinite loop.
 *
 * #\type:  Invalid type defined in <armv6/entry.h>
 */
.macro handle_invalid_entry type
	/* Adjust return address to 1 instr back */
	sub lr, lr, #4
	/* Save clobbered registers, because code is interrupting */
	push {r0-r3, r12, lr}
	mov r0, #\type
	bl show_invalid_entry_message
	b err_hang
.endm

/*
 * Exception vector table.
 * 8 entries.
 * For each exception we jump to the corresponding label, with an absolute
 * address in order to call the exception handler from C code.
 * We need absolute addresses, cause the vector table will be moved at address 0.
 */
.globl vectors
vectors:
	ldr pc, reset_handler_abs_addr			/* Reset */
	ldr pc, undefined_instr_handler_abs_addr	/* Undefined Instruction */
	ldr pc, swi_handler_abs_addr			/* SWI */
	ldr pc, prefetch_abort_handler_abs_addr		/* Prefetch Abort */
	ldr pc, data_abort_handler_abs_addr		/* Data Abort */
	ldr pc, reserved_handler_abs_addr		/* Reserved */
	ldr pc, irq_handler_abs_addr			/* IRQ */
	ldr pc, fiq_handler_abs_addr			/* FIQ */

/*
 * Exception handlers absolute addresses
 */

reset_handler_abs_addr:			.word reset_handler
undefined_instr_handler_abs_addr:	.word undefined_instr_handler
swi_handler_abs_addr:			.word swi_handler
prefetch_abort_handler_abs_addr:	.word prefetch_abort_handler
data_abort_handler_abs_addr:		.word data_abort_handler
reserved_handler_abs_addr:		.word reserved_handler
irq_handler_abs_addr:			.word irq_handler_asm_wrapper
fiq_handler_abs_addr:			.word fiq_handler

/*
 * Implementation of exception handlers.
 * Calls the appropriate handler function from C code
 */

 /* For other exceptions: We call the handle_invalid_entry macro,
	with the corresponding invalid exception type value. */
reset_handler:
	handle_invalid_entry EXCEPT_RESET
undefined_instr_handler:
	handle_invalid_entry EXCEPT_UNDEFINED_INSTR
swi_handler:
	handle_invalid_entry EXCEPT_SWI
prefetch_abort_handler:
	handle_invalid_entry EXCEPT_PREFECH_ABORT
data_abort_handler:
	handle_invalid_entry EXCEPT_DATA_ABORT
reserved_handler:
	handle_invalid_entry EXCEPT_RESERVED
fiq_handler:
	handle_invalid_entry EXCEPT_FIQ

/*
 * For IRQ: We call the exception handler handle_irq from C code.
 * We switch from IRQ mode to Supervisor mode.
 */

irq_handler_asm_wrapper:
	sub lr, lr, #4		/* Adjust return address to 1 instr back */
	/* We are in IRQ mode,
	 * Store lr and spsr to Supervisor stack,
	 * Save the resulting stack pointer as the current stack pointer
	 */
	srsdb sp!, #0x13	/* mode 0x13: Supervisor mode */
	/* Switch to Supervisor mode with interrupts disabled */
	cpsid if, #0x13
	/* Save clobbered registers, because code is interrupting */
	push {r0-r3, r12, lr}

	and r1, sp, #4	/* Correct the stack's 8 byte alignment */
	sub sp, sp, r1
	push {r1}	/* Save the stack adjustment */
	bl handle_irq	/* Calls handler function in C code */
	pop {r1}	/* Get the stack adjustment */
	add sp, sp, r1	/* Restore stack's alignment */

	/* Restore the caller saved registers */
	pop {r0-r3, r12, lr}
	/* Restore the stored cpsr and return to the address in the stored lr */
	rfeia sp!


/*
 * Function for putting the processor in an infinite loop, in case of error.
 */
.globl err_hang
err_hang:
	b err_hang