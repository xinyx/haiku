#ifndef __ASM_PAGE_32_TYPES_H__
#define __ASM_PAGE_32_TYPES_H__

#include <linux/const.h>

/*
 * This handles the memory map.
 *
 * A __PAGE_OFFSET of 0xC0000000 means that the kernel has
 * a virtual address space of one gigabyte, which limits the
 * amount of physical memory you can use to about 950MB.
 *
 * If you want more physical memory than this then see the CONFIG_HIGHMEM4G
 * and CONFIG_HIGHMEM64G options in the kernel configuration.
 */
#define __PAGE_OFFSET		_AC(CONFIG_PAGE_OFFSET, UL)

#define THREAD_SIZE_ORDER	1
#define THREAD_SIZE		(PAGE_SIZE << THREAD_SIZE_ORDER)

#define __PHYSICAL_MASK_SHIFT	44

#endif /* ! __ASM_PAGE_32_TYPES_H__ */
