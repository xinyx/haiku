#include <generated/autoconf.h>
#ifndef __ASM_ARCHRANDOM_H__
#define __ASM_ARCHRANDOM_H__

#include <asm/processor.h>
#include <asm/cpufeature.h>
#include <asm/alternative.h>
#include <asm/nops.h>

#define RDRAND_RETRY_LOOPS	10

#define RDRAND_INT	".byte 0x0f,0xc7,0xf0"
#define RDSEED_INT	".byte 0x0f,0xc7,0xf8"

# define RDRAND_LONG	".byte 0x48,0x0f,0xc7,0xf0"
# define RDSEED_LONG	".byte 0x48,0x0f,0xc7,0xf8"

#define GET_RANDOM(name, type, rdrand, nop)			\
static inline int name(type *v)					\
{								\
	int ok;							\
	alternative_io("movl $0, %0\n\t"			\
		       nop,					\
		       "\n1: " rdrand "\n\t"			\
		       "jc 2f\n\t"				\
		       "decl %0\n\t"                            \
		       "jnz 1b\n\t"                             \
		       "2:",                                    \
		       X86_FEATURE_RDRAND,                      \
		       ASM_OUTPUT2("=r" (ok), "=a" (*v)),       \
		       "0" (RDRAND_RETRY_LOOPS));		\
	return ok;						\
}

#define GET_SEED(name, type, rdseed, nop)			\
static inline int name(type *v)					\
{								\
	unsigned char ok;					\
	alternative_io("movb $0, %0\n\t"			\
		       nop,					\
		       rdseed "\n\t"				\
		       "setc %0",				\
		       X86_FEATURE_RDSEED,                      \
		       ASM_OUTPUT2("=q" (ok), "=a" (*v)));	\
	return ok;						\
}

#endif /* ! __ASM_ARCHRANDOM_H__ */
