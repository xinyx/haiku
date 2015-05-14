#ifndef __ASM_STRING_32_H__
#define __ASM_STRING_32_H__

#define __HAVE_ARCH_STRCPY

#define __HAVE_ARCH_STRNCPY

#define __HAVE_ARCH_STRCAT

#define __HAVE_ARCH_STRNCAT

#define __HAVE_ARCH_STRCMP

#define __HAVE_ARCH_STRNCMP
extern int strncmp(const char *cs, const char *ct, size_t count);

#define __HAVE_ARCH_STRCHR
extern char *strchr(const char *s, int c);

#define __HAVE_ARCH_STRLEN
extern size_t strlen(const char *s);

#define __HAVE_ARCH_MEMCPY

#define memcpy(t, f, n) __builtin_memcpy(t, f, n)

#define __HAVE_ARCH_MEMMOVE

#define memcmp __builtin_memcmp

#define __HAVE_ARCH_MEMCHR

#define __HAVE_ARCH_STRNLEN

#define __HAVE_ARCH_STRSTR

#define COMMON(x)							\
	asm volatile("rep ; stosl"					\
		     x							\
		     : "=&c" (d0), "=&D" (d1)				\
		     : "a" (eax), "0" (count/4), "1" ((long)s)	\
		     : "memory")

#undef COMMON

#define __HAVE_ARCH_MEMSET

#define memset(s, c, count) __builtin_memset(s, c, count)

/*
 * find the first occurrence of byte 'c', or 1 past the area if none
 */
#define __HAVE_ARCH_MEMSCAN

#endif /* ! __ASM_STRING_32_H__ */
