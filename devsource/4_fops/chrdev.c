#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/kdev_t.h>
#include <linux/cdev.h>
#include <linux/device.h>

/**
 * note:
 * register device,class,driver.
 *  cat /proc/devices  #see devices number
*/

static dev_t dev_num;

static struct cdev cdev_test;

static struct class* pclass;

static struct device* pdevice;


static int chrdev_open (struct inode *inode, struct file *file){
    printk("chrdev_open \n");
    /**
     * hardware init here.
    */
    return 0;
}	

static ssize_t chrdev_read (struct file *file, char __user *buf,
                     size_t size, loff_t *off){
    printk("chrdev_read \n");
    return 0;     
}

static ssize_t chrdev_write (struct file *file, const char __user *buf,
                     size_t size, loff_t *off){
    printk("chrdev_write \n");
    return 0;
}

static int chrdev_release (struct inode *inode, struct file *file){
    printk("chrdev_release \n");
    return 0;
}


static struct file_operations fops = {
    .owner      = THIS_MODULE,
    .open       = chrdev_open,
    .write      = chrdev_write,
    .read       = chrdev_read,
    .release    = chrdev_release
};

static int  chrdev_init(void){
    
    int ret;
    printk("chrdev_init..\n");
    
    ret = alloc_chrdev_region(&dev_num,0,1,"chrdev");
    if(ret < 0){
        printk("alloc_chrdev_region faild.\n");
        return -1;
    } else {
        printk("alloc_chrdev_region success.\n");
        printk("major is %d.\n",MAJOR(dev_num));
        printk("minor is %d.\n",MINOR(dev_num));
    }

    cdev_test.owner = THIS_MODULE;
    cdev_init(&cdev_test,&fops);
    cdev_add(&cdev_test,dev_num,1);

    pclass = class_create(THIS_MODULE, "devtest_class"); /* /sys/class/ */ 
    pdevice = device_create(pclass,NULL,dev_num,NULL,"devtest");/*/dev/*/
    return 0;
}

static void  chrdev_exit(void){
    printk("chrdev_exit..\n");
    unregister_chrdev_region(dev_num,1);
    cdev_del(&cdev_test);
    device_destroy(pclass,dev_num);
    class_destroy(pclass);
}


module_init(chrdev_init);
module_exit(chrdev_exit);

MODULE_LICENSE("GPL");


