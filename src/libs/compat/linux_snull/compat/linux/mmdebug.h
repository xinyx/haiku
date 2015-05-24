#include <generated/autoconf.h>
#ifndef __LINUX_MMDEBUG_H__
#define __LINUX_MMDEBUG_H__

#include <linux/stringify.h>

struct page;

#define VM_BUG_ON(cond) BUILD_BUG_ON_INVALID(cond)
#define VM_BUG_ON_PAGE(cond, page) VM_BUG_ON(cond)

#endif /* ! __LINUX_MMDEBUG_H__ */
