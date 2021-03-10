#ifndef	_MM_H
#define	_MM_H

#define PAGE_SHIFT	12
#define TABLE_SHIFT	9
#define SECTION_SHIFT	(PAGE_SHIFT + TABLE_SHIFT)	/* 21 */

#define PAGE_SIZE	(1 << PAGE_SHIFT)	/* 2^12 = 4096 = 4KB */
#define SECTION_SIZE	(1 << SECTION_SHIFT)	/* 2^21 = 2048KB = 2MB */

#define LOW_MEMORY	(2 * SECTION_SIZE)	/* 2*2MB = 4MB */

#endif
