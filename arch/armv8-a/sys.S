/*
 * scheduler.S - Implementation of syscalls for armv8-a.
 */

#include <armv8-a/sys.h>

/*
 * Wrapper function for write() syscall.
 * - w8 is used for the syscall number by convention.
 * - x0 - x7 are used for syscall arguments.
 * - Allows a syscall to have up to 8 arguments.
 */
.globl call_sys_write
call_sys_write:
	/* Store syscall number in the w8 register. */
	mov w8, #SYS_WRITE_NUMBER
	/* Generate a synchronous exception. */
	svc #0
	ret

/*
 * Wrapper function for malloc() syscall.
 * - w8 is used for the syscall number by convention.
 * - x0 - x7 are used for syscall arguments.
 * - Allows a syscall to have up to 8 arguments.
 */
.globl call_sys_malloc
call_sys_malloc:
	/* Store syscall number in the w8 register. */
	mov w8, #SYS_MALLOC_NUMBER
	/* Generate a synchronous exception. */
	svc #0
	ret

/*
 * Wrapper function for exit() syscall.
 * - w8 is used for the syscall number by convention.
 * - x0 - x7 are used for syscall arguments.
 * - Allows a syscall to have up to 8 arguments.
 */
.globl call_sys_exit
call_sys_exit:
	/* Store syscall number in the w8 register. */
	mov w8, #SYS_EXIT_NUMBER
	/* Generate a synchronous exception. */
	svc #0
	ret

/*
 * Wrapper function for clone() syscall.
 * - w8 is used for the syscall number by convention.
 * - x0 - x7 are used for syscall arguments.
 * - Allows a syscall to have up to 8 arguments.
 */
.globl call_sys_clone
call_sys_clone:
	/*
	 * Saves registers x0 - x3, those registers contain parameters of the
	 * syscall and later will be overwritten by the syscall handler
	 */
	mov x10, x0	/* fn */
	mov x11, x1	/* arg */
	mov x12, x2	/* stack */

	/* Do the system call.  */
	mov x0, x2	/* stack  */
	mov w8, #SYS_EXIT_NUMBER
	/* Generate a synchronous exception. */
	svc #0

	/*
	 * Check return value of syscall handler
	 * If 0, we are executing inside of the newly created thread
	 * In this case, execution goes to thread_start label.
	 * Else, it is the PID of the new task.
	 * This means that we return here right after the syscall finishes and
	 * we are executing inside the original thread.
	 * Just return to the caller in this case.
	 */
	cmp x0, #0
	beq thread_start
	ret


thread_start:
	mov x29, 0

	/* Pick the function arg and execute. */
	mov x0, x11
	blr x10

	/* We are done, pass the return value through x0. */
	mov x8, #SYS_EXIT_NUMBER
	svc 0x0
