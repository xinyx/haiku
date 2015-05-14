#ifndef __ASM_PERCPU_H__
#define __ASM_PERCPU_H__

#define __percpu_seg		fs

#include <linux/kernel.h>
#include <linux/stringify.h>

#define __percpu_prefix		"%%"__stringify(__percpu_seg)":"
#define __my_cpu_offset		this_cpu_read(this_cpu_off)

/*
 * Compared to the generic __my_cpu_offset version, the following
 * saves one instruction and avoids clobbering a temp register.
 */
#define __this_cpu_ptr(ptr)				\
({							\
	unsigned long tcp_ptr__;			\
	__verify_pcpu_ptr(ptr);				\
	asm volatile("add " __percpu_arg(1) ", %0"	\
		     : "=r" (tcp_ptr__)			\
		     : "m" (this_cpu_off), "0" (ptr));	\
	(typeof(*(ptr)) __kernel __force *)tcp_ptr__;	\
})

#define __percpu_arg(x)		__percpu_prefix "%P" #x

/* For arch-specific code, we can use direct single-insn ops (they
 * don't give an lvalue though). */
extern void __bad_percpu_size(void);

#define percpu_from_op(op, var, constraint)		\
({							\
	typeof(var) pfo_ret__;				\
	switch (sizeof(var)) {				\
	case 1:						\
		asm(op "b "__percpu_arg(1)",%0"		\
		    : "=q" (pfo_ret__)			\
		    : constraint);			\
		break;					\
	case 2:						\
		asm(op "w "__percpu_arg(1)",%0"		\
		    : "=r" (pfo_ret__)			\
		    : constraint);			\
		break;					\
	case 4:						\
		asm(op "l "__percpu_arg(1)",%0"		\
		    : "=r" (pfo_ret__)			\
		    : constraint);			\
		break;					\
	case 8:						\
		asm(op "q "__percpu_arg(1)",%0"		\
		    : "=r" (pfo_ret__)			\
		    : constraint);			\
		break;					\
	default: __bad_percpu_size();			\
	}						\
	pfo_ret__;					\
})

/*
 * this_cpu_read() makes gcc load the percpu variable every time it is
 * accessed while this_cpu_read_stable() allows the value to be cached.
 * this_cpu_read_stable() is more efficient and can be used if its value
 * is guaranteed to be valid across cpus.  The current users include
 * get_current() and get_thread_info() both of which are actually
 * per-thread variables implemented as per-cpu variables and thus
 * stable for the duration of the respective task.
 */
#define this_cpu_read_stable(var)	percpu_from_op("mov", var, "p" (&(var)))

#define __this_cpu_read_1(pcp)		percpu_from_op("mov", (pcp), "m"(pcp))
#define __this_cpu_read_2(pcp)		percpu_from_op("mov", (pcp), "m"(pcp))
#define __this_cpu_read_4(pcp)		percpu_from_op("mov", (pcp), "m"(pcp))

#define __this_cpu_write_1(pcp, val)	percpu_to_op("mov", (pcp), val)
#define __this_cpu_write_2(pcp, val)	percpu_to_op("mov", (pcp), val)
#define __this_cpu_write_4(pcp, val)	percpu_to_op("mov", (pcp), val)
#define __this_cpu_add_1(pcp, val)	percpu_add_op((pcp), val)
#define __this_cpu_add_2(pcp, val)	percpu_add_op((pcp), val)
#define __this_cpu_add_4(pcp, val)	percpu_add_op((pcp), val)
#define __this_cpu_and_1(pcp, val)	percpu_to_op("and", (pcp), val)
#define __this_cpu_and_2(pcp, val)	percpu_to_op("and", (pcp), val)
#define __this_cpu_and_4(pcp, val)	percpu_to_op("and", (pcp), val)
#define __this_cpu_or_1(pcp, val)	percpu_to_op("or", (pcp), val)
#define __this_cpu_or_2(pcp, val)	percpu_to_op("or", (pcp), val)
#define __this_cpu_or_4(pcp, val)	percpu_to_op("or", (pcp), val)
#define __this_cpu_xor_1(pcp, val)	percpu_to_op("xor", (pcp), val)
#define __this_cpu_xor_2(pcp, val)	percpu_to_op("xor", (pcp), val)
#define __this_cpu_xor_4(pcp, val)	percpu_to_op("xor", (pcp), val)
#define __this_cpu_xchg_1(pcp, val)	percpu_xchg_op(pcp, val)
#define __this_cpu_xchg_2(pcp, val)	percpu_xchg_op(pcp, val)
#define __this_cpu_xchg_4(pcp, val)	percpu_xchg_op(pcp, val)

#define this_cpu_read_1(pcp)		percpu_from_op("mov", (pcp), "m"(pcp))
#define this_cpu_read_2(pcp)		percpu_from_op("mov", (pcp), "m"(pcp))
#define this_cpu_read_4(pcp)		percpu_from_op("mov", (pcp), "m"(pcp))
#define this_cpu_write_1(pcp, val)	percpu_to_op("mov", (pcp), val)
#define this_cpu_write_2(pcp, val)	percpu_to_op("mov", (pcp), val)
#define this_cpu_write_4(pcp, val)	percpu_to_op("mov", (pcp), val)
#define this_cpu_add_1(pcp, val)	percpu_add_op((pcp), val)
#define this_cpu_add_2(pcp, val)	percpu_add_op((pcp), val)
#define this_cpu_add_4(pcp, val)	percpu_add_op((pcp), val)
#define this_cpu_and_1(pcp, val)	percpu_to_op("and", (pcp), val)
#define this_cpu_and_2(pcp, val)	percpu_to_op("and", (pcp), val)
#define this_cpu_and_4(pcp, val)	percpu_to_op("and", (pcp), val)
#define this_cpu_or_1(pcp, val)		percpu_to_op("or", (pcp), val)
#define this_cpu_or_2(pcp, val)		percpu_to_op("or", (pcp), val)
#define this_cpu_or_4(pcp, val)		percpu_to_op("or", (pcp), val)
#define this_cpu_xor_1(pcp, val)	percpu_to_op("xor", (pcp), val)
#define this_cpu_xor_2(pcp, val)	percpu_to_op("xor", (pcp), val)
#define this_cpu_xor_4(pcp, val)	percpu_to_op("xor", (pcp), val)
#define this_cpu_xchg_1(pcp, nval)	percpu_xchg_op(pcp, nval)
#define this_cpu_xchg_2(pcp, nval)	percpu_xchg_op(pcp, nval)
#define this_cpu_xchg_4(pcp, nval)	percpu_xchg_op(pcp, nval)

#define __this_cpu_add_return_1(pcp, val) percpu_add_return_op(pcp, val)
#define __this_cpu_add_return_2(pcp, val) percpu_add_return_op(pcp, val)
#define __this_cpu_add_return_4(pcp, val) percpu_add_return_op(pcp, val)
#define __this_cpu_cmpxchg_1(pcp, oval, nval)	percpu_cmpxchg_op(pcp, oval, nval)
#define __this_cpu_cmpxchg_2(pcp, oval, nval)	percpu_cmpxchg_op(pcp, oval, nval)
#define __this_cpu_cmpxchg_4(pcp, oval, nval)	percpu_cmpxchg_op(pcp, oval, nval)

#define this_cpu_add_return_1(pcp, val)	percpu_add_return_op(pcp, val)
#define this_cpu_add_return_2(pcp, val)	percpu_add_return_op(pcp, val)
#define this_cpu_add_return_4(pcp, val)	percpu_add_return_op(pcp, val)
#define this_cpu_cmpxchg_1(pcp, oval, nval)	percpu_cmpxchg_op(pcp, oval, nval)
#define this_cpu_cmpxchg_2(pcp, oval, nval)	percpu_cmpxchg_op(pcp, oval, nval)
#define this_cpu_cmpxchg_4(pcp, oval, nval)	percpu_cmpxchg_op(pcp, oval, nval)

#define __this_cpu_cmpxchg_double_4	percpu_cmpxchg8b_double
#define this_cpu_cmpxchg_double_4	percpu_cmpxchg8b_double

#include <asm-generic/percpu.h>

#define DECLARE_EARLY_PER_CPU_READ_MOSTLY(_type, _name)		\
	DECLARE_PER_CPU_READ_MOSTLY(_type, _name);		\
	extern __typeof__(_type) *_name##_early_ptr;		\
	extern __typeof__(_type)  _name##_early_map[]

#endif /* ! __ASM_PERCPU_H__ */
