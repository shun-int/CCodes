#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/miscdevice.h>


static int miscdev_open (struct inode *inode, struct file *file){
    printk("miscdev_open.\n");
    /**
     * hardware init here.
    */
    return 0;
}	

static ssize_t miscdev_read (struct file *file, char __user *buf,
                     size_t size, loff_t *off){
    printk("miscdev_read.\n");
    return 0;     
}

static ssize_t miscdev_write (struct file *file, const char __user *buf,
                     size_t size, loff_t *off){
    printk("miscdev_write.\n");
    return 0;
}

static int miscdev_release (struct inode *inode, struct file *file){
    printk("miscdev_release.\n");
    return 0;
}


static struct file_operations fops = {
    .owner      = THIS_MODULE,
    .open       = miscdev_open,
    .write      = miscdev_write,
    .read       = miscdev_read,
    .release    = miscdev_release
};

struct miscdevice misc_dev={
    .minor      = MISC_DYNAMIC_MINOR,
    .name       = "misc_dev",
    .fops       = &fops
};


static int  miscdev_init(void){
    int ret;
    ret = misc_register(&misc_dev);
    if(ret < 0){
        printk("misc_register err.\n");
    } else {
        printk("misc_register success.\n");
    }

    printk("miscdev_init..\n");
    return 0;
}

static void  miscdev_exit(void){
    misc_deregister(&misc_dev);
    printk("miscdev_exit..\n");
}


module_init(miscdev_init);
module_exit(miscdev_exit);

MODULE_LICENSE("GPL");


