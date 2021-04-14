// SPDX-License-Identifier: GPL-2.0+
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/proc_fs.h>
#include <linux/mount.h>
#include <linux/fs_struct.h>
#include <linux/slab.h>

MODULE_LICENSE("GPL");

struct proc_dir_entry *proc_file_entry;

size_t get_max_mount_size(size_t *number_of_entrys)
{
	struct dentry *curdentry;
	/*
	 * Limited by frame size
	 * PATH_MAX is tricky to define
	 */
	char path[1024];
	// Smallest string is 5: '/   /'
	size_t max_path_size = 5;
	size_t current_size;

	list_for_each_entry(curdentry, &current->fs->root.mnt->mnt_root->d_subdirs, d_child) {
		if (curdentry->d_flags & DCACHE_MOUNTED) {
			(*number_of_entrys)++;
			current_size = strlen(curdentry->d_name.name) +
			strlen(dentry_path_raw(curdentry, path, 1024)) + 3;
			if (current_size > max_path_size)
				max_path_size = current_size;
		}
	}
	//Add 1 for / entry
	(*number_of_entrys)++;
	// + 1 for '\n'
	return max_path_size + 1;
}

static ssize_t read_module(struct file *file, char __user *user, size_t len, loff_t *lofft)
{
	struct dentry *curdentry;
	char path[1024];
	char *buffer;
	size_t number_of_entrys = 0;
	size_t max_length;
	char *to_print;
	int ret;

	max_length = get_max_mount_size(&number_of_entrys);
	to_print = kcalloc(number_of_entrys * max_length, sizeof(*to_print), GFP_KERNEL);
	/*
	 *  Forced to allocate to defined size to avoid stack frame being too big
	 *   (-Wframe-larger-than)
	 */
	buffer = kcalloc(1024, sizeof(*buffer), GFP_KERNEL);
	if (!to_print || !buffer)
		return 0;
	curdentry = current->fs->root.dentry;
	snprintf(buffer, 1024, "root   %s\n", curdentry->d_name.name);
	strcat(to_print, buffer);
	list_for_each_entry(curdentry, &current->fs->root.mnt->mnt_root->d_subdirs, d_child) {
		if (curdentry->d_flags & DCACHE_MOUNTED) {
			snprintf(buffer, 1024, "%s   %s\n", curdentry->d_name.name,
				 dentry_path_raw(curdentry, path, 1024));
			strcat(to_print, buffer);
		}
	}
	ret = simple_read_from_buffer(user, len, lofft, to_print, strlen(to_print));
	kfree(to_print);
	kfree(buffer);
	return ret;
}

const static struct file_operations proc_file_fops = {
	.read  = read_module,
};

int init_module(void)
{
	proc_file_entry = proc_create("mymounts", 0, NULL, &proc_file_fops);
	if (!proc_file_entry)
		return -ENOMEM;
	return 0;
}

void cleanup_module(void)
{
	proc_remove(proc_file_entry);
}
