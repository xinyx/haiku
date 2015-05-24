#ifndef __LINUX_RWSEM_H__
#define __LINUX_RWSEM_H__

#define _LINUX_RWSEM_H

#include <linux/linkage.h>

#include <linux/types.h>
#include <linux/kernel.h>
#include <linux/list.h>
#include <linux/spinlock.h>
#include <linux/atomic.h>

#include <linux/osq_lock.h>

struct rw_semaphore;

struct rw_semaphore {
	long count;
	struct list_head wait_list;
	raw_spinlock_t wait_lock;
#ifdef CONFIG_RWSEM_SPIN_ON_OWNER
	struct optimistic_spin_queue osq; /* spinner MCS lock */
	/*
	 * Write owner. Used as a speculative check to see
	 * if the owner is running on the cpu.
	 */
	struct task_struct *owner;
#endif
#ifdef CONFIG_DEBUG_LOCK_ALLOC
	struct lockdep_map	dep_map;
#endif
};

#include <asm/rwsem.h>

/*
 * lock for reading
 */
extern void down_read(struct rw_semaphore *sem);

/*
 * lock for writing
 */
extern void down_write(struct rw_semaphore *sem);

/*
 * release a read lock
 */
extern void up_read(struct rw_semaphore *sem);

/*
 * release a write lock
 */
extern void up_write(struct rw_semaphore *sem);

#endif /* ! __LINUX_RWSEM_H__ */
