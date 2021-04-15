// SPDX-License-Identifier: GPL-2.0+
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/miscdevice.h>
#include <linux/fs.h>
#include <linux/uaccess.h>

MODULE_LICENSE("GPL");

ssize_t device_read(struct file *file, char *user, size_t size, loff_t *lofft)
{
	return simple_read_from_buffer(user, 8, lofft, "lubenard", 8);
}

ssize_t device_write(struct file *file, const char *user, size_t size, loff_t *lofft)
{
	char user_string[50];

	if (size > 50)
		return -EINVAL;
	if (copy_from_user(user_string, user, size) == 0) {
		printk(KERN_INFO "Try to write to the kernel space string: '%s'", user_string);
		if (strncmp(user_string, "lubenard", size) != 0)
			return -EINVAL;
		printk(KERN_INFO "The user input is good, copying it into kernel");
	}
	return size;
}

const struct file_operations my_fops = {
	.read = device_read,
	.write = device_write,
};

struct miscdevice my_misc_driver = {
	.minor = MISC_DYNAMIC_MINOR,
	.name = "fortytwo",
	.fops = &my_fops,
};

int init_module(void)
{
	int retval;

	printk(KERN_INFO "Module misc char device driver loaded");
	retval = misc_register(&my_misc_driver);
	if (retval) {
		printk(KERN_INFO "Error while registering misc char device");
		return retval;
	}
	return 0;
}

void cleanup_module(void)
{
	misc_deregister(&my_misc_driver);
	printk(KERN_INFO "Module misc char device driver cleaned up.");
}

