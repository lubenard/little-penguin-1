#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/miscdevice.h>
#include <linux/fs.h>
#include <linux/uaccess.h>

MODULE_LICENSE("GPL");

ssize_t device_read(struct file *file, char *user, size_t size, loff_t *lofft); 
ssize_t device_write(struct file *file, const char *user, size_t size, loff_t *lofft);

struct file_operations my_fops = {
	.read = device_read,
	.write = device_write,
};

struct miscdevice my_misc_driver= {
	.minor = MISC_DYNAMIC_MINOR,
	.name = "fortytwo",
	.fops = &my_fops,
};

ssize_t device_read(struct file *file, char *user, size_t size, loff_t *lofft) {
	// We are forced to use a array, or it might cause buffer overflow.
	static char character[8] = "lubenard";
	static int chars_remaining = 8;
	int ret;

	printk(KERN_INFO "Number of bytes to copy %ld, size of user = %ld", copy_to_user(user, character, 8), strlen(user));
	ret = copy_to_user(user, character, 8);
	if (ret)
		return (-EFAULT);
	printk(KERN_INFO "After copy, user is %s with a size of %ld", user, strlen(user));
	return (chars_remaining--);
}

ssize_t device_write(struct file *file, const char *user, size_t size, loff_t *lofft) {
	printk(KERN_INFO "Try to write to the file, user = '%s'", user);
	if (strncmp(user, "lubenard", size) != 0) {
		printk(KERN_INFO "strcmp returns %d", strcmp(user, "lubenard"));
		return (-EINVAL);
	}
	return (0);
}

int init_module(void)
{
	int retval;

	printk(KERN_INFO "Module misc char device driver loaded\n");
	if ((retval = misc_register(&my_misc_driver))) {
		printk(KERN_INFO "Error while registering misc char device");
		return retval;
	}
	printk(KERN_INFO "I got number %d for minor number", my_misc_driver.minor);
	return (0);
}

void cleanup_module(void)
{
	misc_deregister(&my_misc_driver);
	printk(KERN_INFO "Module misc char device driver cleaned up.\n");
}

