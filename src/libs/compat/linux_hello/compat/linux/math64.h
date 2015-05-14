#ifndef __LINUX_MATH64_H__
#define __LINUX_MATH64_H__

#include <linux/types.h>
#include <asm/div64.h>

extern s64 div_s64_rem(s64 dividend, s32 divisor, s32 *remainder);

extern u64 div64_u64(u64 dividend, u64 divisor);

static __always_inline u32
__iter_div_u64_rem(u64 dividend, u32 divisor, u64 *remainder)
{
	u32 ret = 0;

	while (dividend >= divisor) {
		/* The following asm() prevents the compiler from
		   optimising this loop into a modulo operation.  */
		asm("" : "+rm"(dividend));

		dividend -= divisor;
		ret++;
	}

	*remainder = dividend;

	return ret;
}

#endif /* ! __LINUX_MATH64_H__ */
