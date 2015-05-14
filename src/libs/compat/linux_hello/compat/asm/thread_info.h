#ifndef __ASM_THREAD_INFO_H__
#define __ASM_THREAD_INFO_H__

#include <linux/compiler.h>
#include <asm/page.h>
#include <asm/types.h>

struct task_struct;
struct exec_domain;
#include <asm/processor.h>
#include <linux/atomic.h>

struct thread_info {
	struct task_struct	*task;		/* main task structure */
	struct exec_domain	*exec_domain;	/* execution domain */
	__u32			flags;		/* low level flags */
	__u32			status;		/* thread synchronous flags */
	__u32			cpu;		/* current CPU */
	int			preempt_count;	/* 0 => preemptable,
						   <0 => BUG */
	mm_segment_t		addr_limit;
	struct restart_block    restart_block;
	void __user		*sysenter_return;
#ifdef CONFIG_X86_32
	unsigned long           previous_esp;   /* ESP of the previous stack in
						   case of nested (IRQ) stacks
						*/
	__u8			supervisor_stack[0];
#endif
	unsigned int		sig_on_uaccess_error:1;
	unsigned int		uaccess_err:1;	/* uaccess failed */
};

#define TIF_SIGPENDING		2	/* signal pending */
#define TIF_NEED_RESCHED	3	/* rescheduling necessary */

#define current_stack_pointer ({ \
  unsigned long sp; \
  asm("mov %%esp,%0" : "=g" (sp)); \
  sp; \
 })

static inline struct thread_info *current_thread_info(void)
{
	return (struct thread_info *)
		(current_stack_pointer & ~(THREAD_SIZE - 1));
}

#define TS_RESTORE_SIGMASK	0x0008	/* restore signal mask in do_signal() */

#define HAVE_SET_RESTORE_SIGMASK	1

#endif /* ! __ASM_THREAD_INFO_H__ */
