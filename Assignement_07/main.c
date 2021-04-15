// SPDX-License-Identifier: GPL-2.0+
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/debugfs.h>
#include <linux/jiffies.h>
#include <linux/fs.h>
#include <linux/uaccess.h>

MODULE_LICENSE("GPL");

#define FOO_READING 1
#define FOO_WRITING 2
#define FOO_IDLE 0

struct dentry *debugfs_folder;
struct dentry *debugfs_id;
struct dentry *debugfs_jiffies;
struct dentry *debugfs_foo;

char datas[PAGE_SIZE];
short foo_status;

ssize_t read_id(struct file *file, char *user, size_t size, loff_t *lofft)
{
	return simple_read_from_buffer(user, 8, lofft, "lubenard", 8);
}

ssize_t write_id(struct file *file, const char *user, size_t size, loff_t *lofft)
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

const struct file_operations fops_id = {
	.read = read_id,
	.write = write_id,
};

ssize_t read_curr_jiffies(struct file *file, char *user, size_t size, loff_t *lofft)
{
	char dst_string[10];

	sprintf(dst_string, "%ld", jiffies);
	return simple_read_from_buffer(user, 10, lofft, dst_string, 10);
}

const struct file_operations fops_jiffies = {
	.read = read_curr_jiffies,
};

ssize_t read_foo(struct file *file, char *user, size_t size, loff_t *lofft)
{
	int len = strlen(datas);
	int ret;

	if (foo_status == FOO_IDLE) {
		foo_status = FOO_READING;
		ret = simple_read_from_buffer(user, len, lofft, datas, len);
		foo_status = FOO_IDLE;
		return ret;
	}
	return 0;
}

ssize_t write_foo(struct file *file, const char *user, size_t size, loff_t *lofft)
{
	ssize_t ret;

	if (size > PAGE_SIZE)
		return -EINVAL;
	if (foo_status == FOO_IDLE) {
		foo_status = FOO_WRITING;
		ret = copy_from_user(datas, user, size);
		if (ret != 0)
			return -EINVAL;
		foo_status = FOO_IDLE;
		return size;
	}
	return 0;
}

const struct file_operations fops_foo = {
	.read = read_foo,
	.write = write_foo,
};

int init_module(void)
{
	// This variable is used to clean when module is unloaded
	debugfs_folder = debugfs_create_dir("fortytwo", 0);
	if (debugfs_folder == 0)
		return 1;
	debugfs_id = debugfs_create_file("id", 0666, debugfs_folder, 0, &fops_id);
	debugfs_jiffies = debugfs_create_file("jiffies", 0444, debugfs_folder, 0, &fops_jiffies);
	debugfs_foo = debugfs_create_file("foo", 0644, debugfs_folder, 0, &fops_foo);
	foo_status = FOO_IDLE; 
	return 0;
}

void cleanup_module(void)
{
	debugfs_remove(debugfs_id);
	debugfs_remove(debugfs_jiffies);
	debugfs_remove(debugfs_foo);
	debugfs_remove(debugfs_folder);
}

