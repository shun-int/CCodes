#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/kdev_t.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/uaccess.h>
#include <linux/errno.h>

struct sdev {
    dev_t dev_num;
    struct cdev cdev_test;
    struct class* pclass;
    struct device* pdevice;
}dev_test;


static int chrdev_open (struct inode *inode, struct file *file){
    printk("chrdev_open \n");
    file->private_data = &dev_test;
    /**
     * hardware init here.
    */
    return 0;
}	

static ssize_t chrdev_read (struct file *file, char __user *buf,
                     size_t size, loff_t *off){
    //struct sdev* psdev = (struct sdev*)file->private_data;
    char kbuf[32] = "data copy to usr test";
    printk("chrdev_read \n");
    if(copy_to_user(buf,kbuf,strlen(kbuf)) !=0 ){
        printk("copy_to_user err.\n");
        return -1;
    }
    return 0;     
}

static ssize_t chrdev_write (struct file *file, const char __user *buf,
                     size_t size, loff_t *off){
    //struct sdev* psdev = (struct sdev*)file->private_data;
    char kbuf[32] = {0};put_user
    printk("chrdev_write \n");
    if(copy_from_user(kbuf,buf,size) != 0){
        printk("copy_from_user err.\n");
    }else{
        printk("kbuf : %s\n",kbuf);
    }
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
    
    ret = alloc_chrdev_region(&dev_test.dev_num,0,1,"chrdev");
    if(ret < 0){
        printk("alloc_chrdev_region faild.\n");
        goto err_alloc_chrdev_region;
    } else {
        printk("alloc_chrdev_region success.\n");
        printk("major is %d.\n",MAJOR(dev_test.dev_num));
        printk("minor is %d.\n",MINOR(dev_test.dev_num));
    }

    dev_test.cdev_test.owner = THIS_MODULE;
    cdev_init(&dev_test.cdev_test,&fops);
    ret = cdev_add(&dev_test.cdev_test,dev_test.dev_num,1);
    if(ret<0){
        goto err_cdev_add;
    }
    dev_test.pclass = class_create(THIS_MODULE, "devtest_class"); /* /sys/class/ */ 
    if(IS_ERR(dev_test.pclass)){
        ret = PTR_ERR(dev_test.pclass);
        goto err_class_create;
    }
    dev_test.pdevice = device_create(dev_test.pclass,NULL,dev_test.dev_num,NULL,"devtest");/*/dev/*/
    if(IS_ERR(dev_test.pdevice)){
        ret = PTR_ERR(dev_test.pdevice);
        goto err_device_create;
    }
    return 0;

err_device_create:
    class_destroy(dev_test.pclass);
err_class_create:
    cdev_del(&dev_test.cdev_test);
err_cdev_add:
    unregister_chrdev_region(dev_test.dev_num,1);
err_alloc_chrdev_region:
    return ret;
}

static void  chrdev_exit(void){
    printk("chrdev_exit..\n");
    unregister_chrdev_region(dev_test.dev_num,1);
    cdev_del(&dev_test.cdev_test);
    device_destroy(dev_test.pclass,dev_test.dev_num);
    class_destroy(dev_test.pclass);
}


module_init(chrdev_init);
module_exit(chrdev_exit);

MODULE_LICENSE("GPL");


