#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/proc_fs.h>
#include <linux/mount.h>
#include <linux/fs.h>
#include <linux/fs_struct.h>

MODULE_LICENSE("GPL");

struct proc_dir_entry *proc_file_entry;

static ssize_t read_module(struct file *file, char __user *user, size_t len, loff_t *lofft); 

static const struct file_operations proc_file_fops = {
	.read  = read_module,
};

//char *buffer;

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
			//printk(KERN_INFO "JE ME FAIS BAISER");
			(*number_of_entrys)++;
			current_size = strlen(curdentry->d_name.name) + strlen(dentry_path_raw(curdentry, path, 1024)) + 3;
			printk(KERN_INFO "%s have a length of %zu", curdentry->d_name.name, current_size);
			if (current_size > max_path_size)
				max_path_size = current_size;
		}
	}
	
	printk(KERN_INFO "maxpath_size is %zu", max_path_size);
	return max_path_size;
}

static ssize_t read_module(struct file *file, char __user *user, size_t len, loff_t *lofft) 
{
	/*struct dentry *curdentry;
	char path[PATH_MAX];
	char to_print[PATH_MAX];

	curdentry = current->fs->root.dentry;
	//snprintf(buffer, 1024, "%-*s%s\n", max, "root", curdentry->d_name.name);
	printk(KERN_INFO "%s is mounted %s", curdentry->d_name.name, dentry_path_raw(curdentry, path, 200));
	list_for_each_entry(curdentry, &current->fs->root.mnt->mnt_root->d_subdirs, d_child) {
		if (curdentry->d_flags & DCACHE_MOUNTED) {
			printk(KERN_INFO "%s is mounted %s", curdentry->d_name.name, dentry_path_raw(curdentry, path, PATH_MAX));
			snprintf(user, PATH_MAX - 1, "%s %s\n", curdentry->d_name.name, dentry_path_raw(curdentry, path, PATH_MAX));
		}
	}
	return simple_read_from_buffer(user, len, lofft, );*/
	//get_number_of_entrys();
	size_t test = 0;
	get_max_mount_size(&test);
	printk(KERN_INFO "test = %zu", test);
	return 0;
}

int init_module(void)
{
	proc_file_entry = proc_create("mymounts", 0, NULL, &proc_file_fops);
  	if (!proc_file_entry)
   		return -ENOMEM;
  	return (0);
}

void cleanup_module(void)
{
	proc_remove(proc_file_entry);
}
