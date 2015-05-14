#ifndef __ASM_BARRIER_H__
#define __ASM_BARRIER_H__

#include <asm/alternative.h>
#include <asm/nops.h>

# define smp_rmb()	barrier()

# define smp_wmb()	barrier()

/*
 * Stop RDTSC speculation. This is needed when you need to use RDTSC
 * (or get_cycles or vread that possibly accesses the TSC) in a defined
 * code region.
 *
 * (Could use an alternative three way for this if there was one.)
 */
static __always_inline void rdtsc_barrier(void)
{
	alternative(ASM_NOP3, "mfence", X86_FEATURE_MFENCE_RDTSC);
	alternative(ASM_NOP3, "lfence", X86_FEATURE_LFENCE_RDTSC);
}

#endif /* ! __ASM_BARRIER_H__ */
