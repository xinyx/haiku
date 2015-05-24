#ifndef __LINUX_RTNETLINK_H__
#define __LINUX_RTNETLINK_H__

#include <linux/mutex.h>
#include <linux/netdevice.h>
#include <linux/wait.h>
#include <uapi/linux/rtnetlink.h>

/**
 * rtnl_dereference - fetch RCU pointer when updates are prevented by RTNL
 * @p: The pointer to read, prior to dereferencing
 *
 * Return the value of the specified RCU-protected pointer, but omit
 * both the smp_read_barrier_depends() and the ACCESS_ONCE(), because
 * caller holds RTNL.
 */
#define rtnl_dereference(p)					\
	rcu_dereference_protected(p, lockdep_rtnl_is_held())

#endif /* ! __LINUX_RTNETLINK_H__ */
