#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/kdev_t.h>
#include <linux/cdev.h>
#include <linux/errno.h>

struct led_dev{
    dev_t led_num;
    struct cdev led_cdev;
    struct class* pled_class;
    struct device* pled_device;
};

struct led_dev led1;

ssize_t led_write (struct file *file, const char __user *buf,
        size_t size, loff_t *off){
    printk("led_open.\n");
    return 0;
}
int led_open (struct inode *inode, struct file *file){
    printk("led_write.\n");
    return 0;
}
int led_release (struct inode *inode, struct file *file){
    printk("led_release.\n");
    return 0;
}
	
struct file_operations fops={
    .owner      = THIS_MODULE,
    .open       = led_open,
    .write      = led_write,
    .release    = led_release
};

static int led_init(void){
    int ret;
    ret = alloc_chrdev_region(&led1.led_num,0,1,"led");
    if(ret<0){
        printk("alloc_chrdev_region err.\n");
        goto err_alloc_chrdev_region;
    }
    led1.led_cdev.owner = THIS_MODULE;
    cdev_init(&led1.led_cdev,&fops);
    ret = cdev_add(&led1.led_cdev,led1.led_num,1);
    if(ret<0){
        printk("cdev_add err.\n");
        goto err_cdev_add;
    }
    led1.pled_class = class_create(THIS_MODULE,"led");
    if(IS_ERR(led1.pled_class)){
        ret = PTR_ERR(led1.pled_class);
        goto err_class_create;
    }
    led1.pled_device = device_create(led1.pled_class,NULL,led1.led_num,NULL,"led");
    if(IS_ERR(led1.pled_device)){
        ret = PTR_ERR(led1.pled_device);
        goto err_device_create;
    }
    return 0;

err_device_create:
    class_destroy(led1.pled_class);
err_class_create:
    cdev_del(&led1.led_cdev);
err_cdev_add:
    unregister_chrdev_region(led1.led_num,1);
err_alloc_chrdev_region:
    return ret;
}

static void led_exit(void){
    unregister_chrdev_region(led1.led_num,1);
    cdev_del(&led1.led_cdev);
    device_destroy(led1.pled_class,led1.led_num);
    class_destroy(led1.pled_class);
}

module_init(led_init);
module_exit(led_exit);

MODULE_LICENSE("GPL");

