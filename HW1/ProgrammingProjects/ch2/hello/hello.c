#include <linux/kernel.h>
#include <linux/module.h> 

int init_module(void) 
{ 
    pr_info("HELLO: LOADED\n"); 
    return 0; 
} 


void cleanup_module(void) 
{ 
    pr_info("HELLO: REMOVED\n"); 
} 

MODULE_DESCRIPTION("Chapter 2 - Hello");
MODULE_AUTHOR("Sunny");
MODULE_LICENSE("GPL");

 
