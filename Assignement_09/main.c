#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/proc_fs.h>

MODULE_LICENSE("GPL");

struct proc_dir_entry *proc_file_entry;

static ssize_t read_module(struct file *file, char __user *ubuf,size_t count, loff_t *ppos); 

static const struct file_operations proc_file_fops = {
 .read  = read_module,
};

static ssize_t read_module(struct file *file, char __user *ubuf,size_t count, loff_t *ppos) 
{
	printk( KERN_DEBUG "read handler\n");
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
