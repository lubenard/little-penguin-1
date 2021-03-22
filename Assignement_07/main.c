#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/debugfs.h>
#include <linux/jiffies.h> 

#include <linux/fs.h>
#include <linux/uaccess.h>

MODULE_LICENSE("GPL");

struct dentry *debugfs_folder;
struct dentry *debugfs_id;
struct dentry *debugfs_jiffies;
struct dentry *debugfs_foo;

ssize_t device_read(struct file *file, char *user, size_t size, loff_t *lofft); 
ssize_t device_write(struct file *file, const char *user, size_t size, loff_t *lofft);

struct file_operations fops_id = {
	.read = device_read,
	.write = device_write,
};


ssize_t read_curr_jiffies(struct file *file, char *user, size_t size, loff_t *lofft); 

struct file_operations fops_id = {
	.read = read_curr_jiffies,
};

int init_module(void)
{
	// This variable is used to clean when module is unloaded
	debugfs_folder = debugfs_create_dir("fortytwo", 0);
	if (debugfs_folder == 0)
		return (1);
	debugfs_id = debugfs_create_file("id", 0777, debugfs_folder, 0, &fops_id);
	debugfs_jiffies = debugfs_create_file("jiffies", 0444, debugfs_folder, 0, &fops_id);
	debugfs_foo = debugfs_create_file("foo", 0644, debugfs_folder, 0, &fops_id);
	return (0);
}

void cleanup_module(void)
{
	debugfs_remove(debugfs_id);
	debugfs_remove(debugfs_jiffies);
	debugfs_remove(debugfs_foo);
	debugfs_remove(debugfs_folder);
}

ssize_t read_curr_jiffies(struct file *file, char *user, size_t size, loff_t *lofft) {
	char *dst_string;
	static int chars_remaining = 1;
	int ret;
	sprintf(dst_string, "%ld\n", jiffies);
	
	ret = copy_to_user(user, dst_string, 8);
	if (ret)
		return (-EFAULT);
	if (chars_remaining) {
		chars_remaining = 0;
		return (8);
	} else {
		chars_remaining = 1;
		return (0);
	}
}


ssize_t device_read(struct file *file, char *user, size_t size, loff_t *lofft) {
	// We are forced to use a array, or it might cause buffer overflow.
	static char character[8] = "lubenard";
	static int chars_remaining = 1;
	int ret;

	//
	ret = copy_to_user(user, character, 8);
	if (ret)
		return (-EFAULT);
	if (chars_remaining) {
		chars_remaining = 0;
		return (8);
	} else {
		chars_remaining = 1;
		return (0);
	}
}

ssize_t device_write(struct file *file, const char *user, size_t size, loff_t *lofft) {
	printk(KERN_INFO "Try to write to the file, user = '%s'", user);
	if (strncmp(user, "lubenard", size) != 0)
		return (-EINVAL);
	printk(KERN_INFO "The user input is good, copying it into kernel");
	return (size);
}

