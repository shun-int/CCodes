#include <linux/init.h>
#include <linux/module.h>


static int  dev_init(void){
    printk("dev_init..\n");
    return 0;
}

static void  dev_exit(void){
    printk("dev_exit..\n");
}


module_init(dev_init);
module_exit(dev_exit);

MODULE_LICENSE("GPL");


