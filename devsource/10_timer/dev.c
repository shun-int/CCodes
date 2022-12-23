#include <linux/init.h>
#include <linux/module.h>
#include <linux/timer.h>

void timer_callback(struct timer_list *);
DEFINE_TIMER(test_timer,timer_callback);


void timer_callback(struct timer_list *tm){
    printk("timer_callback..\n");
    mod_timer(&test_timer,jiffies + 1*HZ);
}

static int  dev_init(void){
    printk("dev_init..\n");
    test_timer.expires = jiffies + 1*HZ;
    add_timer(&test_timer);
    return 0;
}

static void  dev_exit(void){
    printk("dev_exit..\n");
    del_timer(&test_timer);
}


module_init(dev_init);
module_exit(dev_exit);

MODULE_LICENSE("GPL");


