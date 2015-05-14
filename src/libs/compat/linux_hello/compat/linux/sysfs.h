#ifndef __LINUX_SYSFS_H__
#define __LINUX_SYSFS_H__

#include <linux/compiler.h>
#include <linux/errno.h>
#include <linux/list.h>
#include <linux/lockdep.h>
#include <linux/kobject_ns.h>
#include <linux/atomic.h>

struct kobject;
struct module;

struct attribute {
	const char		*name;
	umode_t			mode;
#ifdef CONFIG_DEBUG_LOCK_ALLOC
	bool			ignore_lockdep:1;
	struct lock_class_key	*key;
	struct lock_class_key	skey;
#endif
};

struct sysfs_ops {
	ssize_t	(*show)(struct kobject *, struct attribute *,char *);
	ssize_t	(*store)(struct kobject *,struct attribute *,const char *, size_t);
	const void *(*namespace)(struct kobject *, const struct attribute *);
};

struct sysfs_dirent;

#endif /* ! __LINUX_SYSFS_H__ */
