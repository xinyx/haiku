#include <linux/printk.h>
#include <debug.h>

#define DDE_WEAK __attribute__((weak))

#define dde_dummy_printf(...)
#define dde_printf(...) dde_dummy_printf(__VA_ARGS__)

//#define printk(fmt, args...) do{debug_puts(fmt, ##args);} while(0)


static int len(const char * a) {
	int i = 0;
	for(i = 0; a[i] != '\0'; i ++);
	return i;
}

/*
 */
DDE_WEAK int printk(const char * a, ...) {
	//dde_printf("printk not implemented\n");
	
	/*
	 * simplify printk in haiku
	 * @xinyx
	 */
	debug_puts(a, len(a));
	return 0;
}
