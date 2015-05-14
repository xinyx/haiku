#ifndef __LINUX_STRING_H__
#define __LINUX_STRING_H__

#include <linux/compiler.h>	/* for inline */
#include <linux/types.h>	/* for size_t */
#include <linux/stddef.h>	/* for NULL */

#include <uapi/linux/string.h>

/*
 * Include machine specific inline routines
 */
#include <asm/string.h>

extern char * strrchr(const char *,int);

extern char *strim(char *);

#endif /* ! __LINUX_STRING_H__ */
