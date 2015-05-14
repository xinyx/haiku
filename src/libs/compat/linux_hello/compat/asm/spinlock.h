#ifndef __ASM_SPINLOCK_H__
#define __ASM_SPINLOCK_H__

#include <linux/atomic.h>
#include <asm/page.h>
#include <asm/processor.h>
#include <linux/compiler.h>
#include <asm/paravirt.h>

# define LOCK_PTR_REG "a"

# define UNLOCK_LOCK_PREFIX

/*
 * Ticket locks are conceptually two parts, one indicating the current head of
 * the queue, and the other indicating the current tail. The lock is acquired
 * by atomically noting the tail and incrementing it by one (thus adding
 * ourself to the queue and noting our position), then waiting until the head
 * becomes equal to the the initial value of the tail.
 *
 * We use an xadd covering *both* parts of the lock, to increment the tail and
 * also load the position of the head, which takes care of memory ordering
 * issues and should be optimal for the uncontended case. Note the tail must be
 * in the high part, because a wide xadd increment of the low part would carry
 * up and contaminate the high part.
 */
static __always_inline void __ticket_spin_lock(arch_spinlock_t *lock)
{
	register struct __raw_tickets inc = { .tail = 1 };

	inc = xadd(&lock->tickets, inc);

	for (;;) {
		if (inc.head == inc.tail)
			break;
		cpu_relax();
		inc.head = ACCESS_ONCE(lock->tickets.head);
	}
	barrier();		/* make sure nothing creeps before the lock is taken */
}

static __always_inline int __ticket_spin_trylock(arch_spinlock_t *lock)
{
	arch_spinlock_t old, new;

	old.tickets = ACCESS_ONCE(lock->tickets);
	if (old.tickets.head != old.tickets.tail)
		return 0;

	new.head_tail = old.head_tail + (1 << TICKET_SHIFT);

	/* cmpxchg is a full barrier, so nothing can move before it */
	return cmpxchg(&lock->head_tail, old.head_tail, new.head_tail) == old.head_tail;
}

static __always_inline void __ticket_spin_unlock(arch_spinlock_t *lock)
{
	__add(&lock->tickets.head, 1, UNLOCK_LOCK_PREFIX);
}

static inline int __ticket_spin_is_locked(arch_spinlock_t *lock)
{
	struct __raw_tickets tmp = ACCESS_ONCE(lock->tickets);

	return tmp.tail != tmp.head;
}

static inline int __ticket_spin_is_contended(arch_spinlock_t *lock)
{
	struct __raw_tickets tmp = ACCESS_ONCE(lock->tickets);

	return (__ticket_t)(tmp.tail - tmp.head) > 1;
}

static inline int arch_spin_is_locked(arch_spinlock_t *lock)
{
	return __ticket_spin_is_locked(lock);
}

static inline int arch_spin_is_contended(arch_spinlock_t *lock)
{
	return __ticket_spin_is_contended(lock);
}
#define arch_spin_is_contended	arch_spin_is_contended

static __always_inline void arch_spin_lock(arch_spinlock_t *lock)
{
	__ticket_spin_lock(lock);
}

static inline void arch_spin_unlock_wait(arch_spinlock_t *lock)
{
	while (arch_spin_is_locked(lock))
		cpu_relax();
}

#undef READ_LOCK_SIZE
#undef READ_LOCK_ATOMIC
#undef WRITE_LOCK_ADD
#undef WRITE_LOCK_SUB
#undef WRITE_LOCK_CMP

#define ARCH_HAS_SMP_MB_AFTER_LOCK

#endif /* ! __ASM_SPINLOCK_H__ */
