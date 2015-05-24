#include <generated/autoconf.h>
#ifndef __UAPI_ASM_GENERIC_ERRNO_H__
#define __UAPI_ASM_GENERIC_ERRNO_H__

#include <asm-generic/errno-base.h>

#define	ENOSYS		38	/* Function not implemented */

#define	EWOULDBLOCK	EAGAIN	/* Operation would block */

#define	EOPNOTSUPP	95	/* Operation not supported on transport endpoint */

#define	ENOBUFS		105	/* No buffer space available */

#endif /* ! __UAPI_ASM_GENERIC_ERRNO_H__ */
