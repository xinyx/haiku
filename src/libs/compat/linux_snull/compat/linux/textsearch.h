#ifndef __LINUX_TEXTSEARCH_H__
#define __LINUX_TEXTSEARCH_H__

#include <linux/types.h>
#include <linux/list.h>
#include <linux/kernel.h>
#include <linux/err.h>
#include <linux/slab.h>

struct module;

struct ts_config;

/**
 * struct ts_state - search state
 * @offset: offset for next match
 * @cb: control buffer, for persistent variables of get_next_block()
 */
struct ts_state
{
	unsigned int		offset;
	char			cb[40];
};

/**
 * struct ts_ops - search module operations
 * @name: name of search algorithm
 * @init: initialization function to prepare a search
 * @find: find the next occurrence of the pattern
 * @destroy: destroy algorithm specific parts of a search configuration
 * @get_pattern: return head of pattern
 * @get_pattern_len: return length of pattern
 * @owner: module reference to algorithm
 */
struct ts_ops
{
	const char		*name;
	struct ts_config *	(*init)(const void *, unsigned int, gfp_t, int);
	unsigned int		(*find)(struct ts_config *,
					struct ts_state *);
	void			(*destroy)(struct ts_config *);
	void *			(*get_pattern)(struct ts_config *);
	unsigned int		(*get_pattern_len)(struct ts_config *);
	struct module		*owner;
	struct list_head	list;
};

/**
 * struct ts_config - search configuration
 * @ops: operations of chosen algorithm
 * @flags: flags
 * @get_next_block: callback to fetch the next block to search in
 * @finish: callback to finalize a search
 */
struct ts_config
{
	struct ts_ops		*ops;
	int 			flags;

	/**
	 * get_next_block - fetch next block of data
	 * @consumed: number of bytes consumed by the caller
	 * @dst: destination buffer
	 * @conf: search configuration
	 * @state: search state
	 *
	 * Called repeatedly until 0 is returned. Must assign the
	 * head of the next block of data to &*dst and return the length
	 * of the block or 0 if at the end. consumed == 0 indicates
	 * a new search. May store/read persistent values in state->cb.
	 */
	unsigned int		(*get_next_block)(unsigned int consumed,
						  const u8 **dst,
						  struct ts_config *conf,
						  struct ts_state *state);

	/**
	 * finish - finalize/clean a series of get_next_block() calls
	 * @conf: search configuration
	 * @state: search state
	 *
	 * Called after the last use of get_next_block(), may be used
	 * to cleanup any leftovers.
	 */
	void			(*finish)(struct ts_config *conf,
					  struct ts_state *state);
};

/**
 * textsearch_next - continue searching for a pattern
 * @conf: search configuration
 * @state: search state
 *
 * Continues a search looking for more occurrences of the pattern.
 * textsearch_find() must be called to find the first occurrence
 * in order to reset the state.
 *
 * Returns the position of the next occurrence of the pattern or
 * UINT_MAX if not match was found.
 */
static inline unsigned int textsearch_next(struct ts_config *conf,
					   struct ts_state *state)
{
	unsigned int ret = conf->ops->find(conf, state);

	if (conf->finish)
		conf->finish(conf, state);

	return ret;
}

#define TS_PRIV_ALIGNTO	8
#define TS_PRIV_ALIGN(len) (((len) + TS_PRIV_ALIGNTO-1) & ~(TS_PRIV_ALIGNTO-1))

#endif /* ! __LINUX_TEXTSEARCH_H__ */
