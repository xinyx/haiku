#ifndef __ASM_PAGE_H__
#define __ASM_PAGE_H__

#include <linux/types.h>

#include <asm/page_types.h>

#include <asm/page_64.h>

struct page;

#include <linux/range.h>

#define __pa(x)		__phys_addr((unsigned long)(x))

/*
 * We need __phys_reloc_hide() here because gcc may assume that there is no
 * overflow during __pa() calculation and can optimize it unexpectedly.
 * Newer versions of gcc provide -fno-strict-overflow switch to handle this
 * case properly. Once all supported versions of gcc understand it, we can
 * remove this Voodoo magic stuff. (i.e. once gcc3.x is deprecated)
 */
#define __pa_symbol(x) \
	__phys_addr_symbol(__phys_reloc_hide((unsigned long)(x)))

#define __va(x)			((void *)((unsigned long)(x)+PAGE_OFFSET))

/*
 * virt_to_page(kaddr) returns a valid pointer if and only if
 * virt_addr_valid(kaddr) returns true.
 */
#define virt_to_page(kaddr)	pfn_to_page(__pa(kaddr) >> PAGE_SHIFT)

#include <asm-generic/memory_model.h>
#include <asm-generic/getorder.h>

#define __HAVE_ARCH_GATE_AREA 1

#endif /* ! __ASM_PAGE_H__ */
