#include <linux/kernel.h>
#include <linux/module.h> 

MODULE_LICENSE("GPL");

int init_module(void) 
{ 
    pr_info("Hello world.\n"); 
    return 0; 
} 


void cleanup_module(void) 
{ 
    pr_info("Goodbye world.\n"); 
} 

 