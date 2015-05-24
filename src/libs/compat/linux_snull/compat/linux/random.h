#include <generated/autoconf.h>
#ifndef __LINUX_RANDOM_H__
#define __LINUX_RANDOM_H__

#include <uapi/linux/random.h>

extern void get_random_bytes(void *buf, int nbytes);

u32 prandom_u32(void);

/*
 * Handle minimum values for seeds
 */
static inline u32 __seed(u32 x, u32 m)
{
	return (x < m) ? x + m : x;
}

# include <asm/archrandom.h>

#endif /* ! __LINUX_RANDOM_H__ */
