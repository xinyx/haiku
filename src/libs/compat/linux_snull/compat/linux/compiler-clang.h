#ifndef __LINUX_COMPILER_CLANG_H__
#define __LINUX_COMPILER_CLANG_H__

#undef uninitialized_var
#define uninitialized_var(x) x = *(&(x))

#endif /* ! __LINUX_COMPILER_CLANG_H__ */
