#ifndef __ASM_ATOMIC64_32_H__
#define __ASM_ATOMIC64_32_H__

#include <linux/compiler.h>
#include <linux/types.h>
#include <asm/processor.h>

typedef struct {
	u64 __aligned(8) counter;
} atomic64_t;

#define __ATOMIC64_DECL(sym) void atomic64_##sym(atomic64_t *, ...)

#define ATOMIC64_DECL_ONE __ATOMIC64_DECL

#define __alternative_atomic64(f, g, out, in...) \
	asm volatile("call %P[func]" \
		     : out : [func] "i" (atomic64_##g##_cx8), ## in)

#define ATOMIC64_DECL(sym) ATOMIC64_DECL_ONE(sym##_cx8)

#define alternative_atomic64(f, out, in...) \
	__alternative_atomic64(f, f, ASM_OUTPUT2(out), ## in)

ATOMIC64_DECL(read);
ATOMIC64_DECL(set);
ATOMIC64_DECL(xchg);
ATOMIC64_DECL(add_return);
ATOMIC64_DECL(sub_return);
ATOMIC64_DECL(inc_return);
ATOMIC64_DECL(dec_return);
ATOMIC64_DECL(dec_if_positive);
ATOMIC64_DECL(inc_not_zero);
ATOMIC64_DECL(add_unless);

#undef ATOMIC64_DECL
#undef ATOMIC64_DECL_ONE
#undef __ATOMIC64_DECL

/**
 * atomic64_add_return - add and return
 * @i: integer value to add
 * @v: pointer to type atomic64_t
 *
 * Atomically adds @i to @v and returns @i + *@v
 */
static inline long long atomic64_add_return(long long i, atomic64_t *v)
{
	alternative_atomic64(add_return,
			     ASM_OUTPUT2("+A" (i), "+c" (v)),
			     ASM_NO_INPUT_CLOBBER("memory"));
	return i;
}

/*
 * Other variants with different arithmetic operators:
 */
static inline long long atomic64_sub_return(long long i, atomic64_t *v)
{
	alternative_atomic64(sub_return,
			     ASM_OUTPUT2("+A" (i), "+c" (v)),
			     ASM_NO_INPUT_CLOBBER("memory"));
	return i;
}

static inline long long atomic64_inc_return(atomic64_t *v)
{
	long long a;
	alternative_atomic64(inc_return, "=&A" (a),
			     "S" (v) : "memory", "ecx");
	return a;
}

static inline long long atomic64_dec_return(atomic64_t *v)
{
	long long a;
	alternative_atomic64(dec_return, "=&A" (a),
			     "S" (v) : "memory", "ecx");
	return a;
}

#undef alternative_atomic64
#undef __alternative_atomic64

#endif /* ! __ASM_ATOMIC64_32_H__ */
