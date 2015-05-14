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

static int hello_init(void)
{
	printk("Hello, world\n");
	return 0;
}

static void hello_exit(void)
{
	printk("Goodbye, cruel world\n");
}

//module_init(hello_init);
//module_exit(hello_exit);

#define DEVICE_NAME "linux_hello"

int32 api_version = B_CUR_DRIVER_API_VERSION;

static status_t
hello_open(const char *name, uint32 flags, void **cookie)
{
	*cookie = NULL;
	//kprintf("hello opened!\n");
	debug_puts("hello opened!\n", 14);
	return B_OK;
}

static status_t
hello_close(void *cookie)
{
	//kprintf("hello closed!\n");
	debug_puts("hello closed!\n", 14);
	return B_OK;
}

static status_t
hello_freecookie(void *cookie)
{
	//kprintf("hello free!\n");
	debug_puts("hello free!\n", 12);
	return B_OK;
}

static status_t
hello_ioctl(void *cookie, uint32 op, void *buffer, size_t length)
{
	//kprintf("hello ioctl!\n");
	debug_puts("hello ioctl!\n", 13);
	if (op == TCGETA) {
		return B_OK;
	}

	return EPERM;
}

static status_t
hello_read(void *cookie, off_t pos, void *Buffer, size_t *length)
{
	*length = 0;
	//kprintf("hello reads!\n");
	debug_puts("hello reads!\n", 13);
	return B_OK;
}

static status_t
hello_write(void *cookie, off_t pos, const void *buffer, size_t *_length)
{
	//kprintf("hello writes!\n");
	debug_puts("hello writes!\n", 14);

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
		&hello_open,
		&hello_close,
		&hello_freecookie,
		&hello_ioctl,
		&hello_read,
		&hello_write,
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
	hello_init();
	return B_OK;
}

void
uninit_driver(void)
{
	hello_exit();
}

