#ifndef __LINUX_IDR_H__
#define __LINUX_IDR_H__

#include <linux/types.h>
#include <linux/bitops.h>
#include <linux/init.h>
#include <linux/rcupdate.h>

/*
 * We want shallower trees and thus more bits covered at each layer.  8
 * bits gives us large enough first layer for most use cases and maximum
 * tree depth of 4.  Each idr_layer is slightly larger than 2k on 64bit and
 * 1k on 32bit.
 */
#define IDR_BITS 8
#define IDR_SIZE (1 << IDR_BITS)
#define IDR_MASK ((1 << IDR_BITS)-1)

struct idr_layer {
	int			prefix;	/* the ID prefix of this idr_layer */
	int			layer;	/* distance from leaf */
	struct idr_layer __rcu	*ary[1<<IDR_BITS];
	int			count;	/* When zero, we can release it */
	union {
		/* A zero bit means "space here" */
		DECLARE_BITMAP(bitmap, IDR_SIZE);
		struct rcu_head		rcu_head;
	};
};

struct idr {
	struct idr_layer __rcu	*hint;	/* the last layer allocated from */
	struct idr_layer __rcu	*top;
	int			layers;	/* only valid w/o concurrent changes */
	int			cur;	/* current pos for cyclic allocation */
	spinlock_t		lock;
	int			id_free_cnt;
	struct idr_layer	*id_free;
};

void *idr_find_slowpath(struct idr *idp, int id);

/*
 * IDA - IDR based id allocator, use when translation from id to
 * pointer isn't necessary.
 *
 * IDA_BITMAP_LONGS is calculated to be one less to accommodate
 * ida_bitmap->nr_busy so that the whole struct fits in 128 bytes.
 */
#define IDA_CHUNK_SIZE		128	/* 128 bytes per chunk */
#define IDA_BITMAP_LONGS	(IDA_CHUNK_SIZE / sizeof(long) - 1)

struct ida_bitmap {
	long			nr_busy;
	unsigned long		bitmap[IDA_BITMAP_LONGS];
};

struct ida {
	struct idr		idr;
	struct ida_bitmap	*free_bitmap;
};

int ida_get_new_above(struct ida *ida, int starting_id, int *p_id);

#endif /* ! __LINUX_IDR_H__ */
