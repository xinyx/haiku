#ifndef __LINUX_KERNEL_H__
#define __LINUX_KERNEL_H__

#include <linux/linkage.h>
#include <linux/stddef.h>
#include <linux/types.h>
#include <linux/compiler.h>
#include <linux/bitops.h>
#include <linux/log2.h>
#include <linux/typecheck.h>
#include <linux/printk.h>
#include <linux/dynamic_debug.h>
#include <asm/byteorder.h>
#include <uapi/linux/kernel.h>

#define LONG_MAX	((long)(~0UL>>1))

#define DIV_ROUND_UP(n,d) (((n) + (d) - 1) / (d))

# include <asm/div64.h>

struct pt_regs;

# define might_resched() do { } while (0)

  void __might_sleep(const char *file, int line, int preempt_offset);
/**
 * might_sleep - annotation for functions that can sleep
 *
 * this macro will print a stack trace if it is executed in an atomic
 * context (spinlock, irq-handler, ...).
 *
 * This is a useful debugging help to be able to catch problems early and not
 * be bitten later when the calling function happens to sleep when it is not
 * supposed to.
 */
# define might_sleep() \
	do { __might_sleep(__FILE__, __LINE__, 0); might_resched(); } while (0)

int __must_check _kstrtoul(const char *s, unsigned int base, unsigned long *res);
int __must_check _kstrtol(const char *s, unsigned int base, long *res);

int __must_check kstrtoull(const char *s, unsigned int base, unsigned long long *res);
int __must_check kstrtoll(const char *s, unsigned int base, long long *res);

int __must_check kstrtouint(const char *s, unsigned int base, unsigned int *res);
int __must_check kstrtoint(const char *s, unsigned int base, int *res);

int __must_check kstrtoull_from_user(const char __user *s, size_t count, unsigned int base, unsigned long long *res);
int __must_check kstrtoll_from_user(const char __user *s, size_t count, unsigned int base, long long *res);

int __must_check kstrtouint_from_user(const char __user *s, size_t count, unsigned int base, unsigned int *res);
int __must_check kstrtoint_from_user(const char __user *s, size_t count, unsigned int base, int *res);

extern const char hex_asc[];
#define hex_asc_lo(x)	hex_asc[((x) & 0x0f)]
#define hex_asc_hi(x)	hex_asc[((x) & 0xf0) >> 4]

static inline char *hex_byte_pack(char *buf, u8 byte)
{
	*buf++ = hex_asc_hi(byte);
	*buf++ = hex_asc_lo(byte);
	return buf;
}

#define max(x, y) ({				\
	typeof(x) _max1 = (x);			\
	typeof(y) _max2 = (y);			\
	(void) (&_max1 == &_max2);		\
	_max1 > _max2 ? _max1 : _max2; })

/*
 * ..and if you can't take the strict
 * types, you can specify one yourself.
 *
 * Or not use min/max/clamp at all, of course.
 */
#define min_t(type, x, y) ({			\
	type __min1 = (x);			\
	type __min2 = (y);			\
	__min1 < __min2 ? __min1: __min2; })

/**
 * container_of - cast a member of a structure out to the containing structure
 * @ptr:	the pointer to the member.
 * @type:	the type of the container struct this is embedded in.
 * @member:	the name of the member within the struct.
 *
 */
#define container_of(ptr, type, member) ({			\
	const typeof( ((type *)0)->member ) *__mptr = (ptr);	\
	(type *)( (char *)__mptr - offsetof(type,member) );})

#endif /* ! __LINUX_KERNEL_H__ */
