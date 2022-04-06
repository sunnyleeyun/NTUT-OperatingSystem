#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/list.h>
#include <linux/types.h> 
#include <linux/slab.h>

struct birthday 
{
	int day;
	int month;
	int year;
	struct list_head list;
};

static LIST_HEAD(birthday_list);

int birthdayList_init(void) 
{
	printk(KERN_INFO "BIRTHDAY_LIST: LOADING\n");
	
	int i, d = 8, m = 4, y = 1994;
	for (i = 0; i < 10; ++i)
	{ 
		// setup birthday struct
		struct birthday *curr;
		curr = kmalloc(sizeof(*curr), GFP_KERNEL);
		curr->day = d;
		curr->month = m;
		curr->year = y;
		INIT_LIST_HEAD(&curr->list);
		list_add_tail(&curr->list, &birthday_list);

		// update d, m, y randomly
		d = (d + m + y) % 28; if (d == 0) d++;
		m = (m + y - d) % 12; if (m == 0) m++;
		y += (m - d);
	}

	struct birthday *birthdayPtr;

	list_for_each_entry(birthdayPtr, &birthday_list, list) {
		printk(
			KERN_INFO "BIRTHDAY_LIST: Month: %d; Day: %d; Year: %d\n", 
			birthdayPtr->month, 
			birthdayPtr->day,
			birthdayPtr->year
		);
	};

	printk(KERN_INFO "BIRTHDAY_LIST: LOADED\n");
	return 0;
}

void birthdayList_exit(void) 
{

	printk(KERN_INFO "BIRTHDAY_LIST: REMOVING\n");

	struct birthday *birthdayPtr, *next;

	list_for_each_entry_safe(birthdayPtr, next, &birthday_list, list) {
		printk(
			KERN_INFO "BIRTHDAY_LIST: REMOVING -- Month: %d; Day: %d; Year: %d\n",
			birthdayPtr->month,
			birthdayPtr->day,
			birthdayPtr->year
		);
		list_del(&birthdayPtr->list);
		kfree(birthdayPtr);
	}

	printk(KERN_INFO "BIRTHDAY_LIST: REMOVED\n");
};

module_init(birthdayList_init);
module_exit(birthdayList_exit);

MODULE_DESCRIPTION("Chapter 2 - Birthday List");
MODULE_AUTHOR("Sunny");
MODULE_LICENSE("GPL");
