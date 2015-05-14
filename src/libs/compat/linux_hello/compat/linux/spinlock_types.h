#ifndef __LINUX_SPINLOCK_TYPES_H__
#define __LINUX_SPINLOCK_TYPES_H__

#define __LINUX_SPINLOCK_TYPES_H

# include <asm/spinlock_types.h>

#include <linux/lockdep.h>

typedef struct raw_spinlock {
	arch_spinlock_t raw_lock;
#ifdef CONFIG_GENERIC_LOCKBREAK
	unsigned int break_lock;
#endif
#ifdef CONFIG_DEBUG_SPINLOCK
	unsigned int magic, owner_cpu;
	void *owner;
#endif
#ifdef CONFIG_DEBUG_LOCK_ALLOC
	struct lockdep_map dep_map;
#endif
} raw_spinlock_t;

typedef struct spinlock {
	union {
		struct raw_spinlock rlock;

#ifdef CONFIG_DEBUG_LOCK_ALLOC
# define LOCK_PADSIZE (offsetof(struct raw_spinlock, dep_map))
		struct {
			u8 __padding[LOCK_PADSIZE];
			struct lockdep_map dep_map;
		};
#endif
	};
} spinlock_t;

#include <linux/rwlock_types.h>

#endif /* ! __LINUX_SPINLOCK_TYPES_H__ */
