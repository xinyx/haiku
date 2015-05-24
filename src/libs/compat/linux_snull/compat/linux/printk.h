#ifndef __LINUX_PRINTK_H__
#define __LINUX_PRINTK_H__

#include <linux/init.h>
#include <linux/kern_levels.h>
#include <linux/linkage.h>
#include <linux/cache.h>

static inline int printk_get_level(const char *buffer)
{
	if (buffer[0] == KERN_SOH_ASCII && buffer[1]) {
		switch (buffer[1]) {
		case '0' ... '7':
		case 'd':	/* KERN_DEFAULT */
			return buffer[1];
		}
	}
	return 0;
}

#define CONSOLE_LOGLEVEL_SILENT  0 /* Mum's the word */

#define CONSOLE_LOGLEVEL_MOTORMOUTH 15	/* You can't shut this one up */

extern int console_printk[];

#define console_loglevel (console_printk[0])

/*
 * Dummy printk for disabled debugging statements to use whilst maintaining
 * gcc's format and side-effect checking.
 */
static inline __printf(1, 2)
int no_printk(const char *fmt, ...)
{
	return 0;
}

/*
 * delete this type
 * @xinyx
 *
 * asmlinkage __printf(1, 2) __cold
 */
int printk(const char *fmt, ...);

/*
 * Please don't use printk_ratelimit(), because it shares ratelimiting state
 * with all other unrelated printk_ratelimit() callsites.  Instead use
 * printk_ratelimited() or plain old __ratelimit().
 */
extern int __printk_ratelimit(const char *func);
#define printk_ratelimit() __printk_ratelimit(__func__)

extern asmlinkage void dump_stack(void) __cold;

#ifndef pr_fmt
#define pr_fmt(fmt) fmt
#endif

#define pr_warning(fmt, ...) \
	printk(KERN_WARNING pr_fmt(fmt), ##__VA_ARGS__)
#define pr_warn pr_warning

#define pr_info(fmt, ...) \
	printk(KERN_INFO pr_fmt(fmt), ##__VA_ARGS__)

#include <linux/dynamic_debug.h>

#define pr_debug(fmt, ...) \
	no_printk(KERN_DEBUG pr_fmt(fmt), ##__VA_ARGS__)

extern const struct file_operations kmsg_fops;

#endif /* ! __LINUX_PRINTK_H__ */
