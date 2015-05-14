#ifndef __UAPI_LINUX_ELF_H__
#define __UAPI_LINUX_ELF_H__

#include <linux/types.h>
#include <linux/elf-em.h>

typedef __u32	Elf32_Addr;
typedef __u16	Elf32_Half;

typedef __u32	Elf32_Word;

typedef struct elf32_sym{
  Elf32_Word	st_name;
  Elf32_Addr	st_value;
  Elf32_Word	st_size;
  unsigned char	st_info;
  unsigned char	st_other;
  Elf32_Half	st_shndx;
} Elf32_Sym;

#define EI_NIDENT	16

#define	ELFCLASS32	1
#define	ELFCLASS64	2

#endif /* ! __UAPI_LINUX_ELF_H__ */
