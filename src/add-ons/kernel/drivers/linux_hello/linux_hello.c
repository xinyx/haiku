/*                                                     
 * $Id: hello.c,v 1.5 2004/10/26 03:32:21 corbet Exp $ 
 */

/**
 * linux headers
 */
//#include <linux/init.h>
//#include <linux/module.h>

/**
 * haiku headers
 */
#include <debug.h>
#include <Drivers.h>
#include <KernelExport.h>
#include <string.h>
#include <termios.h>

//MODULE_LICENSE("Dual BSD/GPL");

static int linux_hello_init(void)
{
	printk("linux_hello, world\n");
	return 0;
}

static void linux_hello_exit(void)
{
	printk("Goodbye, cruel world\n");
}

//module_init(linux_hello_init);
//module_exit(linux_hello_exit);

#define DEVICE_NAME "linux_hello"

int32 api_version = B_CUR_DRIVER_API_VERSION;

static status_t
linux_hello_open(const char *name, uint32 flags, void **cookie)
{
	*cookie = NULL;
	//kprintf("linux_hello opened!\n");
	linux_hello_init();
	return B_OK;
}

static status_t
linux_hello_close(void *cookie)
{
	//kprintf("linux_hello closed!\n");
	linux_hello_exit();
	return B_OK;
}

static status_t
linux_hello_freecookie(void *cookie)
{
	//kprintf("linux_hello free!\n");
	debug_puts("linux_hello free!\n", 18);
	return B_OK;
}

static status_t
linux_hello_ioctl(void *cookie, uint32 op, void *buffer, size_t length)
{
	//kprintf("linux_hello ioctl!\n");
	debug_puts("linux_hello ioctl!\n", 19);
	if (op == TCGETA) {
		return B_OK;
	}

	return EPERM;
}

static status_t
linux_hello_read(void *cookie, off_t pos, void *Buffer, size_t *length)
{
	*length = 0;
	//kprintf("linux_hello reads!\n");
	debug_puts("linux_hello reads!\n", 19);
	return B_OK;
}

static status_t
linux_hello_write(void *cookie, off_t pos, const void *buffer, size_t *_length)
{
	//kprintf("linux_hello writes!\n");
	debug_puts("linux_hello writes!\n", 20);

	return B_OK;
}

status_t
init_hardware(void)
{
	return B_OK;
}

const char **
publish_devices(void)
{
	static const char *devices[] = {
		DEVICE_NAME,
		NULL
	};

	return devices;
}

device_hooks *
find_device(const char *name)
{
	static device_hooks hooks = {
		&linux_hello_open,
		&linux_hello_close,
		&linux_hello_freecookie,
		&linux_hello_ioctl,
		&linux_hello_read,
		&linux_hello_write,
		NULL,
		NULL,
		NULL,
		NULL
	};

	if (!strcmp(name, DEVICE_NAME))
		return &hooks;

	return NULL;
}

status_t
init_driver(void)
{
	return B_OK;
}

void
uninit_driver(void)
{
}

