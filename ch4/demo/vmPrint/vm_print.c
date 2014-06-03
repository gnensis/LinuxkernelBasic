#include <linux/module.h>
#include <linux/init.h>
#include <linux/interrupt.h>
#include <linux/sched.h>

static int pid;

module_param(pid, int, 0644);

static int __init memtest_init(void)
{
	struct task_struct *p;
	struct vm_area_struct *temp;

	printk("The virtual memory areas(VMA) are:\n");
#if 1//kernel version 2.6.32
	p = pid_task(find_vpid(pid), PIDTYPE_PID);
#else//kernel version before 2.6.31
	p = find_task_by_vpid(pid);
#endif
	temp = p->mm->mmap;

	while(temp)
	{
		printk("start:%p\t end:%p\n", (unsigned long*)temp->vm_start, (unsigned long*)temp->vm_end);
		temp = temp->vm_next;
	}

	return 0;
}

static void __exit memtest_exit(void)
{
	printk("Unloading my module\n");
}

module_init(memtest_init);
module_exit(memtest_exit);
MODULE_LICENSE("GPL");



