#ifndef __ASM_NOPS_H__
#define __ASM_NOPS_H__

#define GENERIC_NOP3 0x8d,0x76,0x00
#define GENERIC_NOP4 0x8d,0x74,0x26,0x00

#define _ASM_MK_NOP(x) ".byte " __stringify(x) "\n"

#define ASM_NOP3 _ASM_MK_NOP(GENERIC_NOP3)
#define ASM_NOP4 _ASM_MK_NOP(GENERIC_NOP4)

#endif /* ! __ASM_NOPS_H__ */
