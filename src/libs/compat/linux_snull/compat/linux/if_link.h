#ifndef __LINUX_IF_LINK_H__
#define __LINUX_IF_LINK_H__

#include <uapi/linux/if_link.h>

struct ifla_vf_info {
	__u32 vf;
	__u8 mac[32];
	__u32 vlan;
	__u32 qos;
	__u32 spoofchk;
	__u32 linkstate;
	__u32 min_tx_rate;
	__u32 max_tx_rate;
};

#endif /* ! __LINUX_IF_LINK_H__ */
