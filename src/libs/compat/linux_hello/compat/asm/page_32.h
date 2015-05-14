#ifndef __ASM_PAGE_32_H__
#define __ASM_PAGE_32_H__

#include <asm/page_32_types.h>

#define __phys_addr_nodebug(x)	((x) - PAGE_OFFSET)

#define __phys_addr(x)		__phys_addr_nodebug(x)

#include <linux/string.h>

static inline void clear_page(void *page)
{
	memset(page, 0, PAGE_SIZE);
}

static inline void copy_page(void *to, void *from)
{
	memcpy(to, from, PAGE_SIZE);
}

#endif /* ! __ASM_PAGE_32_H__ */
