#ifndef __UAPI_LINUX_IN_H__
#define __UAPI_LINUX_IN_H__

#include <linux/types.h>
#include <linux/socket.h>

#define IPPROTO_TCP		IPPROTO_TCP

#define IPPROTO_UDP		IPPROTO_UDP

#define IPPROTO_DCCP		IPPROTO_DCCP

#define IPPROTO_ESP		IPPROTO_ESP

#define IPPROTO_AH		IPPROTO_AH

#define IPPROTO_SCTP		IPPROTO_SCTP

#define IPPROTO_UDPLITE		IPPROTO_UDPLITE

#define __SOCK_SIZE__	16		/* sizeof(struct sockaddr)	*/

#define	INADDR_BROADCAST	((unsigned long int) 0xffffffff)

#include <asm/byteorder.h>

#endif /* ! __UAPI_LINUX_IN_H__ */
