#include <generated/autoconf.h>
#ifndef __NET_NEIGHBOUR_H__
#define __NET_NEIGHBOUR_H__

#include <linux/neighbour.h>

#include <linux/atomic.h>
#include <linux/netdevice.h>
#include <linux/skbuff.h>
#include <linux/rcupdate.h>
#include <linux/seq_file.h>
#include <linux/bitmap.h>

#include <linux/err.h>
#include <linux/sysctl.h>
#include <linux/workqueue.h>
#include <net/rtnetlink.h>

#define NUD_CONNECTED	(NUD_PERMANENT|NUD_NOARP|NUD_REACHABLE)

struct neighbour;

enum {
	NEIGH_VAR_MCAST_PROBES,
	NEIGH_VAR_UCAST_PROBES,
	NEIGH_VAR_APP_PROBES,
	NEIGH_VAR_RETRANS_TIME,
	NEIGH_VAR_BASE_REACHABLE_TIME,
	NEIGH_VAR_DELAY_PROBE_TIME,
	NEIGH_VAR_GC_STALETIME,
	NEIGH_VAR_QUEUE_LEN_BYTES,
	NEIGH_VAR_PROXY_QLEN,
	NEIGH_VAR_ANYCAST_DELAY,
	NEIGH_VAR_PROXY_DELAY,
	NEIGH_VAR_LOCKTIME,
#define NEIGH_VAR_DATA_MAX (NEIGH_VAR_LOCKTIME + 1)
	/* Following are used as a second way to access one of the above */
	NEIGH_VAR_QUEUE_LEN, /* same data as NEIGH_VAR_QUEUE_LEN_BYTES */
	NEIGH_VAR_RETRANS_TIME_MS, /* same data as NEIGH_VAR_RETRANS_TIME */
	NEIGH_VAR_BASE_REACHABLE_TIME_MS, /* same data as NEIGH_VAR_BASE_REACHABLE_TIME */
	/* Following are used by "default" only */
	NEIGH_VAR_GC_INTERVAL,
	NEIGH_VAR_GC_THRESH1,
	NEIGH_VAR_GC_THRESH2,
	NEIGH_VAR_GC_THRESH3,
	NEIGH_VAR_MAX
};

struct neigh_parms {
#ifdef CONFIG_NET_NS
	struct net *net;
#endif
	struct net_device *dev;
	struct neigh_parms *next;
	int	(*neigh_setup)(struct neighbour *);
	void	(*neigh_cleanup)(struct neighbour *);
	struct neigh_table *tbl;

	void	*sysctl_table;

	int dead;
	atomic_t refcnt;
	struct rcu_head rcu_head;

	int	reachable_time;
	int	data[NEIGH_VAR_DATA_MAX];
	DECLARE_BITMAP(data_state, NEIGH_VAR_DATA_MAX);
};

struct neigh_statistics {
	unsigned long allocs;		/* number of allocated neighs */
	unsigned long destroys;		/* number of destroyed neighs */
	unsigned long hash_grows;	/* number of hash resizes */

	unsigned long res_failed;	/* number of failed resolutions */

	unsigned long lookups;		/* number of lookups */
	unsigned long hits;		/* number of hits (among lookups) */

	unsigned long rcv_probes_mcast;	/* number of received mcast ipv6 */
	unsigned long rcv_probes_ucast; /* number of received ucast ipv6 */

	unsigned long periodic_gc_runs;	/* number of periodic GC runs */
	unsigned long forced_gc_runs;	/* number of forced GC runs */

	unsigned long unres_discards;	/* number of unresolved drops */
};

struct neighbour {
	struct neighbour __rcu	*next;
	struct neigh_table	*tbl;
	struct neigh_parms	*parms;
	unsigned long		confirmed;
	unsigned long		updated;
	rwlock_t		lock;
	atomic_t		refcnt;
	struct sk_buff_head	arp_queue;
	unsigned int		arp_queue_len_bytes;
	struct timer_list	timer;
	unsigned long		used;
	atomic_t		probes;
	__u8			flags;
	__u8			nud_state;
	__u8			type;
	__u8			dead;
	seqlock_t		ha_lock;
	unsigned char		ha[ALIGN(MAX_ADDR_LEN, sizeof(unsigned long))];
	struct hh_cache		hh;
	int			(*output)(struct neighbour *, struct sk_buff *);
	const struct neigh_ops	*ops;
	struct rcu_head		rcu;
	struct net_device	*dev;
	u8			primary_key[0];
};

struct neigh_ops {
	int			family;
	void			(*solicit)(struct neighbour *, struct sk_buff *);
	void			(*error_report)(struct neighbour *, struct sk_buff *);
	int			(*output)(struct neighbour *, struct sk_buff *);
	int			(*connected_output)(struct neighbour *, struct sk_buff *);
};

struct pneigh_entry {
	struct pneigh_entry	*next;
#ifdef CONFIG_NET_NS
	struct net		*net;
#endif
	struct net_device	*dev;
	u8			flags;
	u8			key[0];
};

#define NEIGH_NUM_HASH_RND	4

struct neigh_hash_table {
	struct neighbour __rcu	**hash_buckets;
	unsigned int		hash_shift;
	__u32			hash_rnd[NEIGH_NUM_HASH_RND];
	struct rcu_head		rcu;
};

struct neigh_table {
	struct neigh_table	*next;
	int			family;
	int			entry_size;
	int			key_len;
	__u32			(*hash)(const void *pkey,
					const struct net_device *dev,
					__u32 *hash_rnd);
	int			(*constructor)(struct neighbour *);
	int			(*pconstructor)(struct pneigh_entry *);
	void			(*pdestructor)(struct pneigh_entry *);
	void			(*proxy_redo)(struct sk_buff *skb);
	char			*id;
	struct neigh_parms	parms;
	int			gc_interval;
	int			gc_thresh1;
	int			gc_thresh2;
	int			gc_thresh3;
	unsigned long		last_flush;
	struct delayed_work	gc_work;
	struct timer_list 	proxy_timer;
	struct sk_buff_head	proxy_queue;
	atomic_t		entries;
	rwlock_t		lock;
	unsigned long		last_rand;
	struct neigh_statistics	__percpu *stats;
	struct neigh_hash_table __rcu *nht;
	struct pneigh_entry	**phash_buckets;
};

struct neighbour *neigh_lookup(struct neigh_table *tbl, const void *pkey,
			       struct net_device *dev);

struct neighbour *__neigh_create(struct neigh_table *tbl, const void *pkey,
				 struct net_device *dev, bool want_ref);
static inline struct neighbour *neigh_create(struct neigh_table *tbl,
					     const void *pkey,
					     struct net_device *dev)
{
	return __neigh_create(tbl, pkey, dev, true);
}
void neigh_destroy(struct neighbour *neigh);
int __neigh_event_send(struct neighbour *neigh, struct sk_buff *skb);

static inline int neigh_hh_output(const struct hh_cache *hh, struct sk_buff *skb)
{
	unsigned int seq;
	int hh_len;

	do {
		seq = read_seqbegin(&hh->hh_lock);
		hh_len = hh->hh_len;
		if (likely(hh_len <= HH_DATA_MOD)) {
			/* this is inlined by gcc */
			memcpy(skb->data - HH_DATA_MOD, hh->hh_data, HH_DATA_MOD);
		} else {
			int hh_alen = HH_DATA_ALIGN(hh_len);

			memcpy(skb->data - hh_alen, hh->hh_data, hh_alen);
		}
	} while (read_seqretry(&hh->hh_lock, seq));

	skb_push(skb, hh_len);
	return dev_queue_xmit(skb);
}

#endif /* ! __NET_NEIGHBOUR_H__ */
