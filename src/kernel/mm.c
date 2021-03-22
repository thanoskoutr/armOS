/**
 * \ingroup memory
 * @file mm.c
 * @brief Implementation of basic memory functions.
 */

#include <stddef.h>

#include <kernel/mm.h>

/**
 * Array that holds status for each page in the system.
 * Status:
 * - Allocated	= 1
 * - Free	= 0
 */
static unsigned short mem_map [PAGING_PAGES] = {0,};

#ifdef AARCH_32
uint32_t get_free_page()
#elif AARCH_64
uint64_t get_free_page()
#endif
{
	/* Iterate over all available memory pages */
	for (size_t i = 0; i < PAGING_PAGES; i++) {
		/* If the page is free */
		if (mem_map[i] == 0) {
			/* Mark as allocated */
			mem_map[i] = 1;
			/* Return the starting address of the page */
			return LOW_MEMORY + i * PAGE_SIZE;
		}
	}
	return 0;
}

#ifdef AARCH_32
void free_page(uint32_t p)
#elif AARCH_64
void free_page(uint64_t p)
#endif
{
	/* Mark page as free */
	mem_map[(p - LOW_MEMORY) / PAGE_SIZE] = 0;
}