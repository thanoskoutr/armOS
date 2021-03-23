/**
 * @file sys.h
 * @brief Definition of syscall handlers and wrappers.
 */

#ifndef SYS_H
#define SYS_H

#include <stdint.h>

/**
 * Syscall write handler.
 * @param buf Param.
 * @details Details.
 * @see See.
 */
void sys_write(char *buf);
/**
 * Syscall fork handler.
 * @return Return.
 * @details Details.
 * @see See.
 */
int sys_fork();


/**
 * Syscall write wrapper.
 * @param buf Param.
 * @details Callable from user code.
 * @see sys.S
 */
void call_sys_write(char *buf);

/**
 * Syscall clone wrapper.
 * @param fn Param.
 * @param arg Param.
 * @param stack Param.
 * @return Return.
 * @details Callable from user code.
 * @see sys.S
 */
#ifdef AARCH_32
int call_sys_clone(uint32_t fn, uint32_t arg, uint32_t stack);
#elif AARCH_64
int call_sys_clone(uint64_t fn, uint64_t arg, uint64_t stack);
#endif

/**
 * Syscall malloc wrapper.
 * @return Return.
 * @details Callable from user code.
 * @see sys.S
 */
unsigned long call_sys_malloc();

/**
 * Syscall exit wrapper.
 * @details Callable from user code.
 * @see sys.S
 */
void call_sys_exit();

#endif