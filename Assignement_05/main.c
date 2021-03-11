#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/miscdevice.h>
#include <linux/fs.h>

MODULE_LICENSE("GPL");

ssize_t device_read(struct file *file, char *user, size_t size, loff_t *lofft); 
ssize_t device_write(struct file *file, const char *user, size_t size, loff_t *lofft);

struct file_operations my_fops = {
	.read = device_read,
	.write = device_write,
};

struct miscdevice my_misc_driver= {
	.minor = MISC_DYNAMIC_MINOR,
	.name = "My misc driver",
	.fops = &my_fops,
};

ssize_t device_read(struct file *file, char *user, size_t size, loff_t *lofft) {
	return (0);
}

ssize_t device_write(struct file *file, const char *user, size_t size, loff_t *lofft) {
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

