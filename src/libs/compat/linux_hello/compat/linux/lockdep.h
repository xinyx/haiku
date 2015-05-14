#ifndef __LINUX_LOCKDEP_H__
#define __LINUX_LOCKDEP_H__

struct task_struct;

/*
 * The class key takes no space if lockdep is disabled:
 */
struct lock_class_key { };

#define LOCK_CONTENDED(_lock, try, lock) \
	lock(_lock)

#define LOCK_CONTENDED_FLAGS(_lock, try, lock, lockfl, flags) \
	lockfl((_lock), (flags))

# define spin_acquire(l, s, t, i)		do { } while (0)
# define spin_release(l, n, i)			do { } while (0)

# define rwlock_acquire(l, s, t, i)		do { } while (0)
# define rwlock_acquire_read(l, s, t, i)	do { } while (0)
# define rwlock_release(l, n, i)		do { } while (0)

#endif /* ! __LINUX_LOCKDEP_H__ */
