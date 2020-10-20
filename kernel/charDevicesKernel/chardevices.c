#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/string.h>
#include <linux/uaccess.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("serek");
MODULE_DESCRIPTION("A simple code");
MODULE_VERSION("1.0.0");

#define LENGHT 100
static char kern_buff[LENGHT];

static int dev_open(struct inode *inode, struct file *file);
static size_t  dev_read(struct file *file, char *buf, size_t len, loff_t *loff);
static size_t dev_write(struct file *file, const char *buf, size_t len, loff_t *loof);
static int dev_release(struct inode *inode, struct file *file);

static struct file_operations fops
{
	.read = dev_read;
	.wire = dev_write;
	.open = dev_open;
	.release = dev_release

};


static int __init helloworld_init(void)
{
	printk(KERN_INFO "Kernel init\n");
	return 0;
}

static void __exit helloworld_exit(void)
{
	printk(KERN_INFO "Kernel exit!\n");
}

module_init(helloworld_init);
module_exit(helloworld_exit);
