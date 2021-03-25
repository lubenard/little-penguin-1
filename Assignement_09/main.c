#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/proc_fs.h>
#include <linux/mount.h>
#include <linux/fs.h>
#include <linux/fs_struct.h>

MODULE_LICENSE("GPL");

struct proc_dir_entry *proc_file_entry;

static ssize_t read_module(struct file *file, char __user *user, size_t count, loff_t *lofft); 

static const struct file_operations proc_file_fops = {
	.read  = read_module,
};

static ssize_t read_module(struct file *file, char __user *user, size_t count, loff_t *lofft) 
{
	struct dentry *curdentry;

	list_for_each_entry(curdentry, &current->fs->root.mnt->mnt_root->d_subdirs, d_child) {
		if (curdentry->d_flags & DCACHE_MOUNTED)
			printk(KERN_INFO "%s is mounted", curdentry->d_name.name);
	}	
	return (0);
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
