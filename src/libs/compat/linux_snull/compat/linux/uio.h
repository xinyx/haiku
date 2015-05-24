#ifndef __LINUX_UIO_H__
#define __LINUX_UIO_H__

#include <linux/kernel.h>
#include <uapi/linux/uio.h>

struct page;

struct iov_iter {
	int type;
	size_t iov_offset;
	size_t count;
	union {
		const struct iovec *iov;
		const struct bio_vec *bvec;
	};
	unsigned long nr_segs;
};

#endif /* ! __LINUX_UIO_H__ */
