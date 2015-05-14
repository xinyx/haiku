#ifndef __ASM_PGTABLE_TYPES_H__
#define __ASM_PGTABLE_TYPES_H__

#include <linux/const.h>
#include <asm/page_types.h>

# include <asm/pgtable_32_types.h>

#include <linux/types.h>

#define PTE_PFN_MASK		((pteval_t)PHYSICAL_PAGE_MASK)

#define PTE_FLAGS_MASK		(~PTE_PFN_MASK)

typedef struct pgprot { pgprotval_t pgprot; } pgprot_t;

typedef struct { pgdval_t pgd; } pgd_t;

static inline pgdval_t native_pgd_val(pgd_t pgd)
{
	return pgd.pgd;
}

#include <asm-generic/pgtable-nopud.h>

static inline pudval_t native_pud_val(pud_t pud)
{
	return native_pgd_val(pud.pgd);
}

typedef struct { pmdval_t pmd; } pmd_t;

static inline pmdval_t native_pmd_val(pmd_t pmd)
{
	return pmd.pmd;
}

static inline pteval_t native_pte_val(pte_t pte)
{
	return pte.pte;
}

#define pgprot_writecombine	pgprot_writecombine

#endif /* ! __ASM_PGTABLE_TYPES_H__ */
