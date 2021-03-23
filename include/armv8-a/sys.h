/**
 * @file sys.h
 * @brief Definition of syscalls for armv8-a.
 */

#ifndef ARM8_SYS_H
#define ARM8_SYS_H

/**
 * Total Number of Syscalls.
 */
#define __NR_syscalls		4

#define SYS_WRITE_NUMBER	0	/**< Syscall Number for write() */
#define SYS_MALLOC_NUMBER	1	/**< Syscall Number for malloc() */
#define SYS_CLONE_NUMBER	2	/**< Syscall Number for clone() */
#define SYS_EXIT_NUMBER		3	/**< Syscall Number for exit() */

#endif