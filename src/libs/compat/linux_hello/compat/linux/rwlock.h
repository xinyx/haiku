#ifndef __LINUX_RWLOCK_H__
#define __LINUX_RWLOCK_H__

 extern void do_raw_read_lock(rwlock_t *lock) __acquires(lock);
#define do_raw_read_lock_flags(lock, flags) do_raw_read_lock(lock)
 extern int do_raw_read_trylock(rwlock_t *lock);
 extern void do_raw_read_unlock(rwlock_t *lock) __releases(lock);
 extern void do_raw_write_lock(rwlock_t *lock) __acquires(lock);
#define do_raw_write_lock_flags(lock, flags) do_raw_write_lock(lock)
 extern int do_raw_write_trylock(rwlock_t *lock);
 extern void do_raw_write_unlock(rwlock_t *lock) __releases(lock);

#endif /* ! __LINUX_RWLOCK_H__ */
