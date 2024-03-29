// SPDX-License-Identifier: GPL-2.0+

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/miscdevice.h>
#include <linux/fs.h>
#include <linux/slab.h>

/* Dont have a license, LOL */
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Louis Solofrizzo <louis@ne02ptzero.me>");
MODULE_DESCRIPTION("Useless module");

char str[PAGE_SIZE];

ssize_t myfd_read(struct file *fp, char __user *user, size_t size, loff_t *offs)
{
	size_t		t;
	size_t		i;
	char		*tmp;
	/*
	 * Malloc like a boss
	 */
	tmp = kmalloc(sizeof(*tmp) * PAGE_SIZE * 2, GFP_KERNEL);
	for (t = strlen(str) - 1, i = 0; t != -1; t--, i++)
		tmp[i] = str[t];
	tmp[i + 1] = 0;
	return simple_read_from_buffer(user, size, offs, tmp, i);
}

ssize_t myfd_write(struct file *fp, const char __user *user, size_t size,
		   loff_t *offs)
{
	ssize_t res;

	res = simple_write_to_buffer(str, size, offs, user, size) + 1;
	/* 0x0 = ’\0’ */
	str[size + 1] = 0;
	return res;
}

static const struct file_operations myfd_fops = {
	.owner = THIS_MODULE,
	.read = &myfd_read,
	.write = &myfd_write,
};

static struct miscdevice myfd_device = {
	.minor = MISC_DYNAMIC_MINOR,
	.name = "reverse",
	.fops = &myfd_fops,
};

static int __init myfd_init(void)
{
	return misc_register(&myfd_device);
}

static void __exit myfd_cleanup(void)
{
	misc_deregister(&myfd_device);
}

module_init(myfd_init);
module_exit(myfd_cleanup);
