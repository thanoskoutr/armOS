/*
 * mm.h - Definition of basic memory sizes and functions.
 */

#ifndef MM_H
#define MM_H

#include <stdint.h>

#include <peripherals/base.h>

#define PAGE_SHIFT	12
#define TABLE_SHIFT 	9
#define SECTION_SHIFT	(PAGE_SHIFT + TABLE_SHIFT)	/* 21 */

/*
 * PAGE_SIZE:	4KB
 * LOW_MEMORY:	4MB (First 4 MB of memory reserved for the kernel image and init task stack)
 * - For kernel at address 0x0: Start of stack, 4MB available for kernel (except stack)
 * - For kernel at address 0x8000: 4064KB available for kernel till 4MB
 * - For kernel at address 0x80000: 3584KB available for kernel till 4MB
 * HIGH_MEMORY:	MMIO_BASE (Start of Memory Mapped Register)
 */
#define PAGE_SIZE	(1 << PAGE_SHIFT)	/* 2^12 = 4096 = 4KB */
#define SECTION_SIZE	(1 << SECTION_SHIFT)	/* 2^21 = 2048KB = 2MB */

#define LOW_MEMORY	(2 * SECTION_SIZE)	/* 2*2MB = 4MB */
#define HIGH_MEMORY	MMIO_BASE

/*
 * PAGING_MEMORY	Available memory for paging
 * PAGING_PAGES:	Available 4KB pages
 */
#define PAGING_MEMORY	(HIGH_MEMORY - LOW_MEMORY)	/* MMIO_BASE - 4MB */
#define PAGING_PAGES	(PAGING_MEMORY / PAGE_SIZE)	/* (MMIO_BASE - 4MB) / 4KB */

/*
 * Functions for allocating and deallocating memory pages
 * get_free_page() - Returns:
 * 	- On success: Starting address of the allocated page
 * 	- On failure: 0
 */
#ifdef AARCH_32
uint32_t get_free_page();
void free_page(uint32_t p);
#elif AARCH_64
uint64_t get_free_page();
void free_page(uint64_t p);
#endif

#endif