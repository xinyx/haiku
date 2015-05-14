#ifndef __ASM_GENERIC_BITOPS_FLS64_H__
#define __ASM_GENERIC_BITOPS_FLS64_H__

#include <asm/types.h>

static __always_inline int fls64(__u64 x)
{
	__u32 h = x >> 32;
	if (h)
		return fls(h) + 32;
	return fls(x);
}

#endif /* ! __ASM_GENERIC_BITOPS_FLS64_H__ */
