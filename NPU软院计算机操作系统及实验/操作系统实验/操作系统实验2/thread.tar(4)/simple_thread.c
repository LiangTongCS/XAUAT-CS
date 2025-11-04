#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/kthread.h>
#include <linux/delay.h>
#include <linux/sched.h>

static struct task_struct *thread_st;

// 线程函数
static int thread_fn(void *unused)
{
while (!kthread_should_stop())
{
printk(KERN_INFO "Kernel Thread: Running\n");
ssleep(5);
}
printk(KERN_INFO "Kernel Thread: Stopping\n");
return 0;
}

// 模块初始化
static int __init init_thread(void)
{
printk(KERN_INFO "Creating Kernel Thread\n");

// 创建内核线程
thread_st = kthread_run(thread_fn, NULL, "simple_thread");
if (thread_st)
printk(KERN_INFO "Kernel Thread Created Successfully\n");
else
printk(KERN_ERR "Cannot create kernel thread\n");

return 0;
}

// 模块退出
static void __exit cleanup_thread(void)
{
printk(KERN_INFO "Cleaning Up\n");
if (thread_st)
{
kthread_stop(thread_st);
printk(KERN_INFO "Kernel Thread Stopped\n");
}
}

module_init(init_thread);
module_exit(cleanup_thread);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Your Name");
MODULE_DESCRIPTION("A Simple Kernel Thread Example");
