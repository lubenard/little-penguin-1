#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/usb.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Lubenard <lubenard@student.fr>");
MODULE_DESCRIPTION("Load correct userspace for usb keyboard");

#define USB_KEYBOARD_VENDOR_ID 0xfff0
#define USB_KEYBOARD_PRODUCT_ID 0xfff0

static const struct usb_device_id usb_keyboard_table[] = {
	{ USB_DEVICE(USB_KEYBOARD_VENDOR_ID, USB_KEYBOARD_PRODUCT_ID) },
	{ }
}

static int usb_keyboard_diconnect(struct usb_interface *interface);

static struct usb_driver usb_keyboard_loader = {
	.name		= "skeleton",
	.probe		= usb_keyboard_connect,
	.disconnect	= usb_keyboard_disconnect,
	.id_table	= usb_keyboard_table,
};

static int usb_keyboard_connect(struct usb_interface *interface,
	       	const struct usb_device_id *id)
{
	printk(KERN_INFO "USB DETECTED");
	return (0);
}

static int usb_keyboard_disconnect(struct usb_interface *interface)
{
	printk(KERN_INFO "USB DISCONNECTED");
	return (0);

}
int init_module(void)
{
	int result;

	/* register module to the kernel */
	result = usb_register(&usb_keyboard_loader);
	if (result < 0)
		printk(KERN_ERR "Failed to register from the kernel for usb_keyboard_loader");
	else
		printk(KERN_INFO "Register is done for usb_keyboard_loader\n");
	return (0);
}

void cleanup_module(void)
{
	usb_deregister(&usb_keyboard_loader);
	printk(KERN_INFO "Cleaning up module.\n");
}


