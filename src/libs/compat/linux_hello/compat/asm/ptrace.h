#ifndef __ASM_PTRACE_H__
#define __ASM_PTRACE_H__

#include <asm/segment.h>
#include <asm/page_types.h>
#include <uapi/asm/ptrace.h>

struct pt_regs {
	unsigned long r15;
	unsigned long r14;
	unsigned long r13;
	unsigned long r12;
	unsigned long bp;
	unsigned long bx;
/* arguments: non interrupts/non tracing syscalls only save up to here*/
	unsigned long r11;
	unsigned long r10;
	unsigned long r9;
	unsigned long r8;
	unsigned long ax;
	unsigned long cx;
	unsigned long dx;
	unsigned long si;
	unsigned long di;
	unsigned long orig_ax;
/* end of arguments */
/* cpu exception frame or undefined */
	unsigned long ip;
	unsigned long cs;
	unsigned long flags;
	unsigned long sp;
	unsigned long ss;
/* top of stack page */
};

#include <linux/init.h>

struct cpuinfo_x86;
struct task_struct;

#define profile_pc profile_pc

extern unsigned long kernel_stack_pointer(struct pt_regs *regs);

#define GET_IP(regs) ((regs)->ip)
#define GET_FP(regs) ((regs)->bp)
#define GET_USP(regs) ((regs)->sp)

#include <asm-generic/ptrace.h>

#define MAX_REG_OFFSET (offsetof(struct pt_regs, ss))

/**
 * regs_within_kernel_stack() - check the address in the stack
 * @regs:	pt_regs which contains kernel stack pointer.
 * @addr:	address which is checked.
 *
 * regs_within_kernel_stack() checks @addr is within the kernel stack page(s).
 * If @addr is within the kernel stack, it returns true. If not, returns false.
 */
static inline int regs_within_kernel_stack(struct pt_regs *regs,
					   unsigned long addr)
{
	return ((addr & ~(THREAD_SIZE - 1))  ==
		(kernel_stack_pointer(regs) & ~(THREAD_SIZE - 1)));
}

#endif /* ! __ASM_PTRACE_H__ */
