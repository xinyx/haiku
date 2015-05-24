#ifndef __ASM_UNISTD_H__
#define __ASM_UNISTD_H__

#include <uapi/asm/unistd.h>

#  include <asm/unistd_64.h>
#  include <asm/unistd_64_x32.h>

#  define __ARCH_WANT_COMPAT_SYS_GETDENTS64
#  define __ARCH_WANT_COMPAT_SYS_PREADV64
#  define __ARCH_WANT_COMPAT_SYS_PWRITEV64

#endif /* ! __ASM_UNISTD_H__ */
