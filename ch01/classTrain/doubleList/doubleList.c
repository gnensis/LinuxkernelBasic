#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/slab.h>
#include <linux/list.h>
#include <linux/sched.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("QSM");

#define N 10

struct numlist
{
	int num;
	struct list_head list;
};

struct numlist numhead;


static int print_pid(void)
{
        struct task_struct *task, *p;
        struct list_head *pos;
        int count = 0;
        printk("hello world enter begin:\n");
        task = &init_task;
        list_for_each(pos, &task->tasks)
        {
                p = list_entry(pos, struct task_struct, tasks);
                count++;
                printk("%d--->%s\n", p->pid, p->comm);
        }

        printk("the number of process is:%d\n", count);

        return 0;
}



static int __init doublelist_init(void)
{
	//
	struct numlist *listnode = NULL;
	struct list_head *pos = NULL;
	struct numlist *p = NULL;
	int i = 0;

	printk("doublelist is starting...\n");
	INIT_LIST_HEAD(&numhead.list);

	for(i = 0; i < N; i++)
	{
		listnode = (struct numlist*)kmalloc(sizeof(struct numlist), GFP_KERNEL);
		if(NULL == listnode)
		{
			return -1;
		}
		listnode->num = i + 1;
		list_add_tail(&listnode->list, &numhead.list);
		printk("Node %d has added to the double list...\n");
	}

	//
	i = 1;
	list_for_each(pos, &numhead.list)
	{
		p = list_entry(pos, struct numlist, list);
		printk("Node %d's data:%d\n", i, p->num);
		i++;
	}


	print_pid();

	return 0;
}

static void __exit doublelist_exit(void)
{
	struct list_head *pos = NULL, *n = NULL;
	struct numlist *p = NULL;
	int i = 0;

	//
	i = 1;
	list_for_each_safe(pos, n, &numhead.list)
	{
		list_del(pos);
		p = list_entry(pos, struct numlist, list);
		if(p)
		{
			kfree(p);
		}
		printk("Node %d has removed from the doublelist...\n", i);
	}

	printk("doublelist is exiting...\n");
}

module_init(doublelist_init);
module_exit(doublelist_exit);

