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
	printk(KERN_INFO "Creating birthday list\n");

	struct birthday *sunny;
	sunny = kmalloc(sizeof(*sunny), GFP_KERNEL);
	sunny->day = 9;
	sunny->month = 1;
	sunny->year = 1996;
	INIT_LIST_HEAD(&sunny->list);
	list_add_tail(&sunny->list, &birthday_list);

	struct birthday *jenny;
	jenny = kmalloc(sizeof(*jenny), GFP_KERNEL);
	jenny->day = 15;
	jenny->month = 10;
	jenny->year = 1998;
	INIT_LIST_HEAD(&jenny->list);
	list_add_tail(&jenny->list, &birthday_list);

	struct birthday *lilly;
	lilly = kmalloc(sizeof(*lilly), GFP_KERNEL);
	lilly->day = 12;
	lilly->month = 7;
	lilly->year = 1997;
	INIT_LIST_HEAD(&lilly->list);
	list_add_tail(&lilly->list, &birthday_list);

	struct birthday *sandy;
	sandy = kmalloc(sizeof(*sandy), GFP_KERNEL);
	sandy->day = 22;
	sandy->month = 1;
	sandy->year = 1957;
	INIT_LIST_HEAD(&sandy->list);
	list_add_tail(&sandy->list, &birthday_list);

	struct birthday *doris;
	doris = kmalloc(sizeof(*doris), GFP_KERNEL);
	doris->day = 1;
	doris->month = 12;
	doris->year = 1935;
	INIT_LIST_HEAD(&doris->list);
	list_add_tail(&doris->list, &birthday_list);

/* Traversing the list */

	printk(KERN_INFO "Traversing birthday list\n");

	struct birthday *birthdayPtr;

	list_for_each_entry(birthdayPtr, &birthday_list, list) {
		printk(KERN_INFO "BIRTHDAY: Month: %d Day: %d Year: %d\n", 
			birthdayPtr->month, 
			birthdayPtr->day,
			birthdayPtr->year);
	};

	return 0;
}

void birthdayList_exit(void) 
{

	printk(KERN_INFO "Removing module\n");

	struct birthday *birthdayPtr, *next;

	list_for_each_entry_safe(birthdayPtr, next, &birthday_list, list) {
		printk(KERN_INFO "REMOVING BIRTHDAY: Month: %d Day: %d Year: %d\n",
			birthdayPtr->month,
			birthdayPtr->day,
			birthdayPtr->year);

		list_del(&birthdayPtr->list);
		kfree(birthdayPtr);
	}
};

module_init(birthdayList_init);
module_exit(birthdayList_exit);

MODULE_DESCRIPTION("Chapter 2");
MODULE_AUTHOR("Yubo");
MODULE_LICENSE("GPL");
