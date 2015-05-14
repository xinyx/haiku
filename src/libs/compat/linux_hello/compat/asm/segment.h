#ifndef __ASM_SEGMENT_H__
#define __ASM_SEGMENT_H__

#include <linux/const.h>

/*
 * The layout of the per-CPU GDT under Linux:
 *
 *   0 - null
 *   1 - reserved
 *   2 - reserved
 *   3 - reserved
 *
 *   4 - unused			<==== new cacheline
 *   5 - unused
 *
 *  ------- start of TLS (Thread-Local Storage) segments:
 *
 *   6 - TLS segment #1			[ glibc's TLS segment ]
 *   7 - TLS segment #2			[ Wine's %fs Win32 segment ]
 *   8 - TLS segment #3
 *   9 - reserved
 *  10 - reserved
 *  11 - reserved
 *
 *  ------- start of kernel segments:
 *
 *  12 - kernel code segment		<==== new cacheline
 *  13 - kernel data segment
 *  14 - default user CS
 *  15 - default user DS
 *  16 - TSS
 *  17 - LDT
 *  18 - PNPBIOS support (16->32 gate)
 *  19 - PNPBIOS support
 *  20 - PNPBIOS support
 *  21 - PNPBIOS support
 *  22 - PNPBIOS support
 *  23 - APM BIOS support
 *  24 - APM BIOS support
 *  25 - APM BIOS support
 *
 *  26 - ESPFIX small SS
 *  27 - per-cpu			[ offset to per-cpu data area ]
 *  28 - stack_canary-20		[ for stack protector ]
 *  29 - unused
 *  30 - unused
 *  31 - TSS for double fault handler
 */
#define GDT_ENTRY_TLS_MIN	6

#define GDT_ENTRY_KERNEL_BASE		(12)

#define GDT_ENTRY_KERNEL_CS		(GDT_ENTRY_KERNEL_BASE+0)

#define GDT_ENTRY_TSS			(GDT_ENTRY_KERNEL_BASE+4)
#define GDT_ENTRY_LDT			(GDT_ENTRY_KERNEL_BASE+5)

/*
 * The GDT has 32 entries
 */
#define GDT_ENTRIES 32

#define __KERNEL_CS	(GDT_ENTRY_KERNEL_CS*8)

#define USER_RPL		0x3

#define SEGMENT_RPL_MASK	0x3

#define NUM_EXCEPTION_VECTORS 32

#define GDT_ENTRY_TLS_ENTRIES 3

#endif /* ! __ASM_SEGMENT_H__ */
