#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/kthread.h>
#include <linux/delay.h>

static struct task_struct *thread_st;

static int thread_fn(void *unused) {
    while (!kthread_should_stop()) {
        printk(KERN_INFO "Thread Running\n");
        ssleep(5);
    }
    printk(KERN_INFO "Thread Stopping\n");
    do_exit(0);
    return 0;
}

static int __init init_thread(void) {
    printk(KERN_INFO "Hello openEuler\n"); // 新增语句
    printk(KERN_INFO "Creating Thread\n");
    thread_st = kthread_run(thread_fn, NULL, "mythread");
    return 0;
}


static void __exit cleanup_thread(void) {
    printk(KERN_INFO "Cleaning Up\n");
    if (thread_st) {
        kthread_stop(thread_st);
        printk(KERN_INFO "Thread stopped");
    }
}

module_init(init_thread);
module_exit(cleanup_thread);
MODULE_LICENSE("GPL");
