#ifndef __LINUX_AIO_H__
#define __LINUX_AIO_H__

#include <linux/list.h>
#include <linux/workqueue.h>
#include <linux/aio_abi.h>
#include <linux/uio.h>
#include <linux/rcupdate.h>

#include <linux/atomic.h>

struct kioctx;
struct kiocb;

typedef int (kiocb_cancel_fn)(struct kiocb *);

struct kiocb {
	struct file		*ki_filp;
	struct kioctx		*ki_ctx;	/* NULL for sync ops */
	kiocb_cancel_fn		*ki_cancel;
	void			*private;

	union {
		void __user		*user;
		struct task_struct	*tsk;
	} ki_obj;

	__u64			ki_user_data;	/* user's data for completion */
	loff_t			ki_pos;
	size_t			ki_nbytes;	/* copy of iocb->aio_nbytes */

	struct list_head	ki_list;	/* the aio core uses this
						 * for cancellation */

	/*
	 * If the aio_resfd field of the userspace iocb is not zero,
	 * this is the underlying eventfd context to deliver events to.
	 */
	struct eventfd_ctx	*ki_eventfd;
};

struct mm_struct;

#endif /* ! __LINUX_AIO_H__ */
