#include <linux/module.h>
#include <linux/init.h>
#include <linux/workqueue.h>

static struct workqueue_struct * queue = NULL;
static struct work_struct work;

static void work_handler(struct work_struct * data)
{
	printk(KERN_ALERT "work handler function.\n");
}

static int __init test_init(void)
{
	printk(KERN_ALERT "workqueue init...\n");

	queue = create_singlethread_workqueue("helloworld");
	if(!queue)
	{
		goto err;
	}

	INIT_WORK(&work, work_handler);
#if 1
	schedule_work(&work);
#else
	schedule_delayed_work(to_delayed_work(&work), 30000);//this makes kernel crash.???
#endif

	return 0;

err:
	return -1;
}

static void __exit test_exit(void)
{
	destroy_workqueue(queue);

	printk(KERN_ALERT "workqueue exit...\n");
}

MODULE_LICENSE("GPL");
module_init(test_init);
module_exit(test_exit);

