/**
 * @file fork.h
 * @brief Definition of fork-related functions.
 */

#ifndef FORK_H
#define FORK_H

#include <stdint.h>
#include <kernel/scheduler.h>

/**
 * \name ESR_EL1
 * @{
 * PSR bits - First 4 bits of SPSR_ELx system registers \n
 * AArch64 Exception level and selected Stack Pointer.
 */
#define PSR_MODE_EL0t	0x00000000	/**< Supported by: SPSR_EL1, SPSR_EL2, SPSR_EL3 */
#define PSR_MODE_EL1t	0x00000004	/**< Supported by: SPSR_EL1, SPSR_EL2, SPSR_EL3 */
#define PSR_MODE_EL1h	0x00000005	/**< Supported by: SPSR_EL1, SPSR_EL2, SPSR_EL3 */
#define PSR_MODE_EL2t	0x00000008	/**< Supported by: SPSR_EL2, SPSR_EL3 */
#define PSR_MODE_EL2h	0x00000009	/**< Supported by: SPSR_EL2, SPSR_EL3 */
#define PSR_MODE_EL3t	0x0000000c	/**< Supported by: SPSR_EL3 */
#define PSR_MODE_EL3h	0x0000000d	/**< Supported by: SPSR_EL3 */
/** @} */

/**
 * Structure that ...
*/
#ifdef AARCH_32
typedef struct {
	uint32_t regs[31];	/**<  */
	uint32_t sp;		/**<  */
	uint32_t pc;		/**<  */
	uint32_t pstate;	/**<  */
} pt_regs;
#elif AARCH_64
typedef struct {
	uint64_t regs[31];	/**<  */
	uint64_t sp;		/**<  */
	uint64_t pc;		/**<  */
	uint64_t pstate;	/**<  */
} pt_regs;
#endif



/**
 * Function for creating a new process.
 * @param clone_flags
 * @param fn A function to execute in a new thread.
 * @param arg An argument that need to be passed to this function.
 * @param stack
 * @return
 * - On success: pid
 * - On failure: -1
 * @details Allocates a new @ref task_struct and makes it available for the scheduler.
 * @see task_struct, get_free_page()
 */
#ifdef AARCH_32
int copy_process(uint32_t clone_flags, uint32_t fn, uint32_t arg, uint32_t stack);
#elif AARCH_64
int copy_process(uint64_t clone_flags, uint64_t fn, uint64_t arg, uint64_t stack);
#endif

/**
 * Function that moves a kernel task to a user task.
 * @param pc Address of the function to execute as a user task.
 * @return
 * - On success: 0
 * - On failure: -1
 * @details Details.
 * @see pt_regs, task_pt_regs(), get_free_page(), memzero()
 */
#ifdef AARCH_32
int move_to_user_mode(uint32_t pc);
#elif AARCH_64
int move_to_user_mode(uint64_t pc);
#endif

/**
 * Calculates the location of the pt_regs area.
 * @param tsk Pointer to the current @ref task_struct.
 * @return The address of the pt_regs.
 * @details The pt_regs area is located at the top of the stack
 * of the newly created task.
 * @see pt_regs, task_struct, THREAD_SIZE
 */
pt_regs *task_pt_regs(task_struct *tsk);

#endif