#include <linux/init.h>
#include <linux/module.h>
#include <linux/platform_device.h>

void p_dev_rsc_release(struct device *dev){
    printk("p_dev_rsc_release..\n");
}

// struct resource p_dev_rsc={ /*test*/
//     [0]={
//         .start  = 0x0005,
//         .end    = 0x0006,
//         .flags  = IORESOURCE_MEM,
//         .name   = "GPIO_DR"
//     }
// };

struct platform_device p_dev_test={
    .name           = "p_dev_test",
    .id             = -1,
    // .resource       = &p_dev_rsc,
    // .num_resources  = ARRAY_SIZE(p_dev_rsc),
    .dev            = {
        .release    = p_dev_rsc_release
    }
};

static int  dev_init(void){
    printk("dev_init..\n");
    return platform_device_register(&p_dev_test);
}

static void  dev_exit(void){
    printk("dev_exit..\n");
    platform_device_unregister(&p_dev_test);
}


module_init(dev_init);
module_exit(dev_exit);

MODULE_LICENSE("GPL");


