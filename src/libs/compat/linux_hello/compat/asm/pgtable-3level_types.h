#ifndef __ASM_PGTABLE_3LEVEL_TYPES_H__
#define __ASM_PGTABLE_3LEVEL_TYPES_H__

#include <linux/types.h>

typedef u64	pteval_t;
typedef u64	pmdval_t;
typedef u64	pudval_t;
typedef u64	pgdval_t;
typedef u64	pgprotval_t;

typedef union {
	struct {
		unsigned long pte_low, pte_high;
	};
	pteval_t pte;
} pte_t;

#define PAGETABLE_LEVELS	3

/*
 * entries per page directory level
 */
#define PTRS_PER_PTE	512

#endif /* ! __ASM_PGTABLE_3LEVEL_TYPES_H__ */
