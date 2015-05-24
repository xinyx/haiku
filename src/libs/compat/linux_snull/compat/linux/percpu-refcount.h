#ifndef __LINUX_PERCPU_REFCOUNT_H__
#define __LINUX_PERCPU_REFCOUNT_H__

#include <linux/atomic.h>
#include <linux/kernel.h>
#include <linux/percpu.h>
#include <linux/rcupdate.h>

struct percpu_ref;
typedef void (percpu_ref_func_t)(struct percpu_ref *);

struct percpu_ref {
	atomic_t		count;
	/*
	 * The low bit of the pointer indicates whether the ref is in percpu
	 * mode; if set, then get/put will manipulate the atomic_t (this is a
	 * hack because we need to keep the pointer around for
	 * percpu_ref_kill_rcu())
	 */
	unsigned __percpu	*pcpu_count;
	percpu_ref_func_t	*release;
	percpu_ref_func_t	*confirm_kill;
	struct rcu_head		rcu;
};

void percpu_ref_kill_and_confirm(struct percpu_ref *ref,
				 percpu_ref_func_t *confirm_kill);

#define PCPU_STATUS_BITS	2
#define PCPU_STATUS_MASK	((1 << PCPU_STATUS_BITS) - 1)
#define PCPU_REF_PTR		0

#define REF_STATUS(count)	(((unsigned long) count) & PCPU_STATUS_MASK)

/**
 * percpu_ref_get - increment a percpu refcount
 * @ref: percpu_ref to get
 *
 * Analagous to atomic_inc().
  */
static inline void percpu_ref_get(struct percpu_ref *ref)
{
	unsigned __percpu *pcpu_count;

	rcu_read_lock_sched();

	pcpu_count = ACCESS_ONCE(ref->pcpu_count);

	if (likely(REF_STATUS(pcpu_count) == PCPU_REF_PTR))
		this_cpu_inc(*pcpu_count);
	else
		atomic_inc(&ref->count);

	rcu_read_unlock_sched();
}

/**
 * percpu_ref_tryget - try to increment a percpu refcount
 * @ref: percpu_ref to try-get
 *
 * Increment a percpu refcount unless its count already reached zero.
 * Returns %true on success; %false on failure.
 *
 * The caller is responsible for ensuring that @ref stays accessible.
 */
static inline bool percpu_ref_tryget(struct percpu_ref *ref)
{
	unsigned __percpu *pcpu_count;
	int ret = false;

	rcu_read_lock_sched();

	pcpu_count = ACCESS_ONCE(ref->pcpu_count);

	if (likely(REF_STATUS(pcpu_count) == PCPU_REF_PTR)) {
		this_cpu_inc(*pcpu_count);
		ret = true;
	} else {
		ret = atomic_inc_not_zero(&ref->count);
	}

	rcu_read_unlock_sched();

	return ret;
}

/**
 * percpu_ref_tryget_live - try to increment a live percpu refcount
 * @ref: percpu_ref to try-get
 *
 * Increment a percpu refcount unless it has already been killed.  Returns
 * %true on success; %false on failure.
 *
 * Completion of percpu_ref_kill() in itself doesn't guarantee that tryget
 * will fail.  For such guarantee, percpu_ref_kill_and_confirm() should be
 * used.  After the confirm_kill callback is invoked, it's guaranteed that
 * no new reference will be given out by percpu_ref_tryget().
 *
 * The caller is responsible for ensuring that @ref stays accessible.
 */
static inline bool percpu_ref_tryget_live(struct percpu_ref *ref)
{
	unsigned __percpu *pcpu_count;
	int ret = false;

	rcu_read_lock_sched();

	pcpu_count = ACCESS_ONCE(ref->pcpu_count);

	if (likely(REF_STATUS(pcpu_count) == PCPU_REF_PTR)) {
		this_cpu_inc(*pcpu_count);
		ret = true;
	}

	rcu_read_unlock_sched();

	return ret;
}

/**
 * percpu_ref_put - decrement a percpu refcount
 * @ref: percpu_ref to put
 *
 * Decrement the refcount, and if 0, call the release function (which was passed
 * to percpu_ref_init())
 */
static inline void percpu_ref_put(struct percpu_ref *ref)
{
	unsigned __percpu *pcpu_count;

	rcu_read_lock_sched();

	pcpu_count = ACCESS_ONCE(ref->pcpu_count);

	if (likely(REF_STATUS(pcpu_count) == PCPU_REF_PTR))
		this_cpu_dec(*pcpu_count);
	else if (unlikely(atomic_dec_and_test(&ref->count)))
		ref->release(ref);

	rcu_read_unlock_sched();
}

#endif /* ! __LINUX_PERCPU_REFCOUNT_H__ */
