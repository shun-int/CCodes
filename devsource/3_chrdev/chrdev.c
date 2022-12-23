#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/kdev_t.h>
#include <linux/cdev.h>
/**
 * note:
 * register device.
*/

static dev_t dev_num;

static struct cdev cdev_test;


static struct file_operations fops = {
    .owner      = THIS_MODULE
    // .open       = chrdev_open,
    // .write      = chrdev_write,
    // .read       = chrdev_read,
    // .release    = chrdev_close
};

static int  chrdev_init(void){
    
    int ret;
    printk("chrdev_init..\n");
    
    ret = alloc_chrdev_region(&dev_num,0,1,"chrdev");
    if(ret < 0){
        printk("alloc_chrdev_region faild.\n");
    } else {
        printk("alloc_chrdev_region success.\n");
    }

    cdev_test.owner = THIS_MODULE;
    cdev_init(&cdev_test,&fops);
    cdev_add(&cdev_test,dev_num,1);
    return 0;
}

static void  chrdev_exit(void){
    printk("chrdev_exit..\n");
    unregister_chrdev_region(dev_num,1);
    cdev_del(&cdev_test);
}


module_init(chrdev_init);
module_exit(chrdev_exit);

MODULE_LICENSE("GPL");


