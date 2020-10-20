#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("serek");
MODULE_DESCRIPTION("A simple code");
MODULE_VERSION("1.0.0");

static int __init helloworld_init(void)
{
	printk(KERN_INFO "Hello world!\n");
	return 0;
}

static void __exit helloworld_exit(void)
{
	printk(KERN_INFO "Goodbye world!\n");
}

module_init(helloworld_init);
module_exit(helloworld_exit);
