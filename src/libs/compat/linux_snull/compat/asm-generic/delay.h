#include <generated/autoconf.h>
#ifndef __ASM_GENERIC_DELAY_H__
#define __ASM_GENERIC_DELAY_H__

#define ndelay(n)							\
	({								\
		if (__builtin_constant_p(n)) {				\
			if ((n) / 20000 >= 1)				\
				__bad_ndelay();				\
			else						\
				__const_udelay((n) * 5ul);		\
		} else {						\
			__ndelay(n);					\
		}							\
	})

#endif /* ! __ASM_GENERIC_DELAY_H__ */
