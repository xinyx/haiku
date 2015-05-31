#include <asm/string_64.h>
#include <asm-generic/bug.h>
#include <linux/etherdevice.h>
#include <linux/jiffies.h>
#include <linux/moduleparam.h>
#include <linux/netdevice.h>
#include <linux/printk.h>
#include <linux/skbuff.h>
#include <linux/slab.h>
#include <linux/spinlock_api_smp.h>

#include <debug.h>

#define DDE_WEAK __attribute__((weak))

#define dde_dummy_printf(...)
#define dde_printf(...) dde_dummy_printf(__VA_ARGS__)

/* Support for loadable net-drivers */
DDE_WEAK struct net_device * alloc_netdev_mqs(int a, const char * b, void (*c)(struct net_device *), unsigned int d, unsigned int e) {
	dde_printf("alloc_netdev_mqs not implemented\n");
	return 0;
}

/*
 */
DDE_WEAK void consume_skb(struct sk_buff * a) {
	dde_printf("consume_skb not implemented\n");
}

/*
 */
DDE_WEAK void ether_setup(struct net_device * a) {
	dde_printf("ether_setup not implemented\n");
}

/*
 */
DDE_WEAK __be16 eth_type_trans(struct sk_buff * a, struct net_device * b) {
	dde_printf("eth_type_trans not implemented\n");
	return 0;
}

/*
 */
DDE_WEAK void free_netdev(struct net_device * a) {
	//dde_printf("free_netdev not implemented\n");
	free(a);
}

/*
 */
volatile unsigned long jiffies;

/*
 */
DDE_WEAK void kfree(const void * a) {
	//dde_printf("kfree not implemented\n");
	free(a);
}

/*
 */
DDE_WEAK void * __kmalloc(size_t a, gfp_t b) {
	//dde_printf("__kmalloc not implemented\n");
	return malloc(a);
}

/*
 * added by xinyx
 */
struct kmem_cache *kmalloc_caches[KMALLOC_SHIFT_HIGH + 1];

DDE_WEAK void *  kmem_cache_alloc_trace(struct kmem_cache *cachep, gfp_t flags, size_t size) {
	dde_printf("kmem_cache_alloc_trace not implemented\n");
	return 0;
}

/*
DDE_WEAK void * __memcpy(void * a, const void * b, size_t c) {
	dde_printf("__memcpy not implemented\n");
	return 0;
}

DDE_WEAK void * memset(void * a, int b, size_t c) {
	dde_printf("memset not implemented\n");	
	return 0;
}
*/

/*
 */
DDE_WEAK void napi_complete(struct napi_struct * a) {
	dde_printf("napi_complete not implemented\n");
}

/*
 */
DDE_WEAK void __napi_schedule(struct napi_struct * a) {
	dde_printf("__napi_schedule not implemented\n");
}

/*
 */
DDE_WEAK struct sk_buff * __netdev_alloc_skb(struct net_device * a, unsigned int b, gfp_t c) {
	dde_printf("__netdev_alloc_skb not implemented\n");
	return 0;
}

/*
 */
DDE_WEAK void netif_napi_add(struct net_device * a, struct napi_struct * b, int (*c)(struct napi_struct *, int), int d) {
	dde_printf("netif_napi_add not implemented\n");
}

/*
 */
DDE_WEAK int netif_receive_skb(struct sk_buff * a) {
	dde_printf("netif_receive_skb not implemented\n");
	return 0;
}

/*
 */
DDE_WEAK int netif_rx(struct sk_buff * a) {
	dde_printf("netif_rx not implemented\n");
	return 0;
}

/*
 */
DDE_WEAK void __netif_schedule(struct Qdisc * a) {
	dde_printf("__netif_schedule not implemented\n");
}

struct kernel_param_ops param_ops_int;

/*
*/
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


/*
 * Please don't use printk_ratelimit(), because it shares ratelimiting state
 * with all other unrelated printk_ratelimit() callsites.  Instead use
 * printk_ratelimited() or plain old __ratelimit().
 */
DDE_WEAK int __printk_ratelimit(const char * a) {
	dde_printf("__printk_ratelimit not implemented\n");
	return 0;
}

/*
*/
DDE_WEAK void _raw_spin_lock(raw_spinlock_t * a) {
	dde_printf("_raw_spin_lock not implemented\n");
}

/*
*/
DDE_WEAK unsigned long _raw_spin_lock_irqsave(raw_spinlock_t * a) {
	dde_printf("_raw_spin_lock_irqsave not implemented\n");
	return 0;
}

/*
*/
DDE_WEAK void _raw_spin_unlock_irqrestore(raw_spinlock_t * a, unsigned long b) {
	dde_printf("_raw_spin_unlock_irqrestore not implemented\n");
}

/*
*/
DDE_WEAK int register_netdev(struct net_device * a) {
	dde_printf("register_netdev not implemented\n");
	return 0;
}

/*
*/
DDE_WEAK unsigned char * skb_push(struct sk_buff * a, unsigned int b) {
	dde_printf("skb_push not implemented\n");
	return 0;
}

/*
 *	Add data to an sk_buff
 */
DDE_WEAK unsigned char * skb_put(struct sk_buff * a, unsigned int b) {
	dde_printf("skb_put not implemented\n");
	return 0;
}

/*
*/
DDE_WEAK void unregister_netdev(struct net_device * a) {
	dde_printf("unregister_netdev not implemented\n");
}

/*
*/
DDE_WEAK void warn_slowpath_null(const char * a, const int b) {
	dde_printf("warn_slowpath_null not implemented\n");
}

