#include <generated/autoconf.h>
#ifndef __UAPI_LINUX_IN6_H__
#define __UAPI_LINUX_IN6_H__

#include <linux/types.h>
#include <linux/libc-compat.h>

struct in6_addr {
	union {
		__u8		u6_addr8[16];
#if __UAPI_DEF_IN6_ADDR_ALT
		__be16		u6_addr16[8];
		__be32		u6_addr32[4];
#endif
	} in6_u;
#define s6_addr			in6_u.u6_addr8
#if __UAPI_DEF_IN6_ADDR_ALT
#define s6_addr16		in6_u.u6_addr16
#define s6_addr32		in6_u.u6_addr32
#endif
};

#endif /* ! __UAPI_LINUX_IN6_H__ */
