#ifndef __ASM_LINKAGE_H__
#define __ASM_LINKAGE_H__

#include <linux/stringify.h>

#undef notrace
#define notrace __attribute__((no_instrument_function))

#define asmlinkage CPP_ASMLINKAGE __attribute__((regparm(0)))

/*
 * Make sure the compiler doesn't do anything stupid with the
 * arguments on the stack - they are owned by the *caller*, not
 * the callee. This just fools gcc into not spilling into them,
 * and keeps it from doing tailcall recursion and/or using the
 * stack slots for temporaries, since they are live and "used"
 * all the way to the end of the function.
 *
 * NOTE! On x86-64, all the arguments are in registers, so this
 * only matters on a 32-bit kernel.
 */
#define asmlinkage_protect(n, ret, args...) \
	__asmlinkage_protect##n(ret, ##args)

#endif /* ! __ASM_LINKAGE_H__ */
