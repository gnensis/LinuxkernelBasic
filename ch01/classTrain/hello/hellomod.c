#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>

static int __init lkp_init(void)
{
	printk("<1>Hello,world from the kernel space...\n");
	return 0;
}

static void __exit lkp_exit(void)
{
	printk("<1>Goodby, crowl world...\n");
}

module_init(lkp_init);
module_exit(lkp_exit);
MODULE_LICENSE("GPL");

