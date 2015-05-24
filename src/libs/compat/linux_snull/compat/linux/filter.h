#include <generated/autoconf.h>
#ifndef __LINUX_FILTER_H__
#define __LINUX_FILTER_H__

#include <linux/atomic.h>
#include <linux/compat.h>
#include <linux/workqueue.h>
#include <uapi/linux/filter.h>

struct sock_filter_int {
	__u8	code;		/* opcode */
	__u8	dst_reg:4;	/* dest register */
	__u8	src_reg:4;	/* source register */
	__s16	off;		/* signed offset */
	__s32	imm;		/* signed immediate constant */
};

struct sock_fprog_kern {
	u16			len;
	struct sock_filter	*filter;
};

struct sk_buff;
struct sock;

struct sk_filter {
	atomic_t		refcnt;
	u32			jited:1,	/* Is our filter JIT'ed? */
				len:31;		/* Number of filter blocks */
	struct sock_fprog_kern	*orig_prog;	/* Original BPF program */
	struct rcu_head		rcu;
	unsigned int		(*bpf_func)(const struct sk_buff *skb,
					    const struct sock_filter_int *filter);
	union {
		struct sock_filter	insns[0];
		struct sock_filter_int	insnsi[0];
		struct work_struct	work;
	};
};

#define BPF_ANC		BIT(15)

#define BPF_ANCILLARY(CODE)	case SKF_AD_OFF + SKF_AD_##CODE:	\
				return BPF_ANC | SKF_AD_##CODE

#include <linux/slab.h>

#endif /* ! __LINUX_FILTER_H__ */
