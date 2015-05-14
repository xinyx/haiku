#ifndef __ASM_GENERIC_PGTABLE_NOPUD_H__
#define __ASM_GENERIC_PGTABLE_NOPUD_H__

/*
 * Having the pud type consist of a pgd gets the size right, and allows
 * us to conceptually access the pgd entry that this pud is folded into
 * without casting.
 */
typedef struct { pgd_t pgd; } pud_t;

#endif /* ! __ASM_GENERIC_PGTABLE_NOPUD_H__ */
