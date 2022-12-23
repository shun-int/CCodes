#include <linux/init.h>
#include <linux/module.h>
#include <linux/platform_device.h>

struct resource p_dev_rsc;

int p_drv_probe(struct platform_device *pdev){
    /**
     * pdev ponit to [p_dev.c: struct platform_device]
     * direct access is not safe.
    */
    printk("p_drv_probe..\n");
    p_dev_rsc = platform_get_resource(pdev,unsigned int, unsigned int);
    /**
     * regiser chr dev or misc..
     * or do some init.
    */
    return 0;
}
int p_drv_remove(struct platform_device *pdev){
    printk("p_drv_remove..\n");
    return 0;
}

// struct platform_device_id  p_drv_idtab={
    // .name       = "p_dev_test"
// };

struct platform_driver p_drv={
    .probe      = p_drv_probe,
    .remove     = p_drv_remove,
    .driver     = {
        .owner  = THIS_MODULE,
        .name   = "p_dev_test",
    },
    // .id_table   = &p_drv_idtab

};

static int  drv_init(void){
    int ret;
    printk("drv_init..\n");
    ret = platform_driver_register(&p_drv);
    if(ret < 0){
        printk("platform_driver_register err.\n");
    }
    return ret;
}

static void  drv_exit(void){
    printk("drv_exit..\n");
    platform_driver_unregister(&p_drv);
}


module_init(drv_init);
module_exit(drv_exit);

MODULE_LICENSE("GPL");


