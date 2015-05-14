#include <linux/printk.h>
#include <debug.h>

#define DDE_WEAK __attribute__((weak))

#define dde_dummy_printf(...)
#define dde_printf(...) dde_dummy_printf(__VA_ARGS__)

//#define printk(fmt, args...) do{debug_puts(fmt, ##args);} while(0)

/*
 */

int printk(const char * a, ...) {
	//dde_printf("printk not implemented\n");
	
	/*
	 * simplify printk in haiku
	 * @xinyx
	 */
	debug_puts(a, sizeof(a));
	return 0;
}
