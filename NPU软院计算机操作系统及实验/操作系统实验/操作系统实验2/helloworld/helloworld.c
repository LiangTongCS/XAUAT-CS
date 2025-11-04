#include <linux/module.h>

MODULE_LICENSE("GPL");

static int __init helloworld_init(void)
{
    printk("Hello World!\n");
    return 0;
}
static void __exit helloworld_exit(void)
{
    printk("Exit Hello World!\n");
}
module_init(helloworld_init);
module_exit(helloworld_exit); 

