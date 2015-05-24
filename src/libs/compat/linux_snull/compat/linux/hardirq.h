#ifndef __LINUX_HARDIRQ_H__
#define __LINUX_HARDIRQ_H__

#include <linux/preempt_mask.h>
#include <linux/lockdep.h>
#include <linux/ftrace_irq.h>
#include <linux/vtime.h>
#include <asm/hardirq.h>

/*
 * Enter irq context (on NO_HZ, update jiffies):
 */
extern void irq_enter(void);

/*
 * Exit irq context and process softirqs if needed:
 */
extern void irq_exit(void);

#endif /* ! __LINUX_HARDIRQ_H__ */
