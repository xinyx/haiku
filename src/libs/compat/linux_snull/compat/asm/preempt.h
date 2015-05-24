#include <generated/autoconf.h>
#ifndef __ASM_PREEMPT_H__
#define __ASM_PREEMPT_H__

#include <asm/rmwcc.h>
#include <asm/percpu.h>
#include <linux/thread_info.h>

DECLARE_PER_CPU(int, __preempt_count);

/*
 * We mask the PREEMPT_NEED_RESCHED bit so as not to confuse all current users
 * that think a non-zero value indicates we cannot preempt.
 */
static __always_inline int preempt_count(void)
{
	return raw_cpu_read_4(__preempt_count) & ~PREEMPT_NEED_RESCHED;
}

static __always_inline void set_preempt_need_resched(void)
{
	raw_cpu_and_4(__preempt_count, ~PREEMPT_NEED_RESCHED);
}

static __always_inline void __preempt_count_add(int val)
{
	raw_cpu_add_4(__preempt_count, val);
}

static __always_inline void __preempt_count_sub(int val)
{
	raw_cpu_add_4(__preempt_count, -val);
}

#endif /* ! __ASM_PREEMPT_H__ */
