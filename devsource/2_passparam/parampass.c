#include <linux/init.h>
#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/fs.h>
#include <linux/kdev_t.h>

/**
 * note:
 * pass param by cmd.
 * register the dev num[dynamic static].
*/

/**
 * \usage [dynamic]:
 * sudo su
 * insmod parampass.ko
 * dmesg 
 * cat /proc/devices
 *      can find:
 *      dmesg printed [major name] 
 *      name is param of [register_chrdev_region]
 * rmmod parampass.ko
 * dmesg
 * cat /proc/devices
 *      cannot find [major name] 
 * \usage [static]:
 * cat /proc/devices
 *      set major(find a dev num that never used).
 * insmod parampass.ko major=2 minor=0
 * dmesg
 * rmmod parampass.ko
 * dmesg
 * cat /proc/devices
 *      make sure the dev num that passbyparam is free.
*/

static int major =0;
static int minor =0;
module_param(major,int,S_IRUGO);
module_param(minor,int,S_IRUGO);

static dev_t dev_num;

static int  parampass_init(void){
    ;
    int ret;
    printk("parampass_init..\n");
    if(major){
        printk("major is %d\n",major);
        printk("minor is %d\n",minor);
        dev_num = MKDEV(major,minor);
        ret = register_chrdev_region(dev_num,1,"parampass");
        if(ret < 0){
            printk("register_chrdev_region faild.\n");
        } else {
            printk("register_chrdev_region success.\n");
        }
    } else {
        ret = alloc_chrdev_region(&dev_num,0,1,"parampass");
        if(ret < 0){
            printk("alloc_chrdev_region faild.\n");
        } else {
            printk("alloc_chrdev_region success.\n");
        }
        major = MAJOR(dev_num);
        minor = MINOR(dev_num);
        printk("major is %d\n",major);
        printk("minor is %d\n",minor);
    }
    return 0;
}

static void  parampass_exit(void){
    printk("parampass_exit..\n");
    unregister_chrdev_region(dev_num,1);
    printk("unregister_chrdev_region...\n");
}


module_init(parampass_init);
module_exit(parampass_exit);

MODULE_LICENSE("GPL");


