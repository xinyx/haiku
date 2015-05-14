#ifndef __LINUX_PREEMPT_H__
#define __LINUX_PREEMPT_H__

#include <linux/thread_info.h>
#include <linux/linkage.h>
#include <linux/list.h>

  extern void add_preempt_count(int val);
  extern void sub_preempt_count(int val);

#define inc_preempt_count() add_preempt_count(1)
#define dec_preempt_count() sub_preempt_count(1)

#define preempt_count()	(current_thread_info()->preempt_count)

asmlinkage void preempt_schedule(void);

#define preempt_check_resched() \
do { \
	if (unlikely(test_thread_flag(TIF_NEED_RESCHED))) \
		preempt_schedule(); \
} while (0)

#define preempt_check_resched_context() preempt_check_resched()

#define preempt_disable() \
do { \
	inc_preempt_count(); \
	barrier(); \
} while (0)

#define sched_preempt_enable_no_resched() \
do { \
	barrier(); \
	dec_preempt_count(); \
} while (0)

#define preempt_enable_no_resched()	sched_preempt_enable_no_resched()

#define preempt_enable() \
do { \
	preempt_enable_no_resched(); \
	barrier(); \
	preempt_check_resched(); \
} while (0)

#define add_preempt_count_notrace(val)			\
	do { preempt_count() += (val); } while (0)
#define sub_preempt_count_notrace(val)			\
	do { preempt_count() -= (val); } while (0)
#define inc_preempt_count_notrace() add_preempt_count_notrace(1)
#define dec_preempt_count_notrace() sub_preempt_count_notrace(1)

#define preempt_disable_notrace() \
do { \
	inc_preempt_count_notrace(); \
	barrier(); \
} while (0)

#define preempt_enable_no_resched_notrace() \
do { \
	barrier(); \
	dec_preempt_count_notrace(); \
} while (0)

#define preempt_enable_notrace() \
do { \
	preempt_enable_no_resched_notrace(); \
	barrier(); \
	preempt_check_resched_context(); \
} while (0)

#endif /* ! __LINUX_PREEMPT_H__ */
