#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/sched/signal.h>


int tasks_lister_linear_init(void)
{
	printk(KERN_INFO "TASKS_LISTER_LINEAR: LOADING\n");

  	struct task_struct *task;

  	for_each_process(task) {
		printk(KERN_INFO "pid: %d | pname: %s | state: %ld\n", task->pid, task->comm, task->state);
 	}

  	printk(KERN_INFO "TASKS_LISTER_LINEAR: LOADED\n");
  	return 0;
};

void tasks_lister_linear_exit(void)
{
  	printk(KERN_INFO "TASKS_LISTER_LINEAR: REMOVED.\n");
};

module_init(tasks_lister_linear_init);
module_exit(tasks_lister_linear_exit);

MODULE_DESCRIPTION("Chapter 3: Part 2");
MODULE_AUTHOR("Sunny");
MODULE_LICENSE("GPL");