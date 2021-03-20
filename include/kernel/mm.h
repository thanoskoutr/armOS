/**
 * @file mm.h
 * @brief Definition of basic memory sizes and functions.
 */

#ifndef MM_H
#define MM_H

#include <stdint.h>

#include <peripherals/base.h>

#define PAGE_SHIFT	12				/**< Bits to shift to define Page size. */
#define TABLE_SHIFT 	9				/**< Bits to shift to define Table size. */
#define SECTION_SHIFT	(PAGE_SHIFT + TABLE_SHIFT)	/**< Bits to shift to define Section size (= 21). */

/**
 * @details `PAGE_SIZE:	4KB`
 * - For kernel at address `0x0`: Start of stack, 4MB available for kernel (except stack).
 * - For kernel at address `0x8000`: 4064KB available for kernel till 4MB.
 * - For kernel at address `0x80000`: 3584KB available for kernel till 4MB.
 */
#define PAGE_SIZE	(1 << PAGE_SHIFT)		/**< - `2^12 = 4096 = 4KB` */
#define SECTION_SIZE	(1 << SECTION_SHIFT)		/**< - `2^21 = 2048KB = 2MB` */

/** 4MB (First 4 MB of memory reserved for the kernel image and init task stack). */
#define LOW_MEMORY	(2 * SECTION_SIZE)		/**< - `2*2MB = 4MB` */
/** Start of Memory Mapped Registers. @see MMIO_BASE */
#define HIGH_MEMORY	MMIO_BASE

/** Available memory for paging */
#define PAGING_MEMORY	(HIGH_MEMORY - LOW_MEMORY)	/**< - `MMIO_BASE - 4MB` */
/** Available 4KB pages */
#define PAGING_PAGES	(PAGING_MEMORY / PAGE_SIZE)	/**< - `(MMIO_BASE - 4MB) / 4KB` */

#ifdef AARCH_32
/**
 * Function for allocating memory pages.
 * @return
 * - On success: Starting address (32-bit) of the allocated page.
 * - On failure: 0
 */
uint32_t get_free_page();
/**
 * Function for deallocating memory pages.
 * @param p 32-bit address of page to be deallocated.
 */
void free_page(uint32_t p);
#elif AARCH_64
/**
 * Function for allocating memory pages.
 * @return
 * - On success: Starting address (64-bit) of the allocated page.
 * - On failure: 0
 */
uint64_t get_free_page();
/**
 * Function for deallocating memory pages.
 * @param p 64-bit address of page to be deallocated.
 */
void free_page(uint64_t p);
#endif

#endif