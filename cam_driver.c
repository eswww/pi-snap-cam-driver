#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/gpio.h>
#include <linux/delay.h>

#define DEV_NAME "cam_driver"

// Using GPIO pin number (Not a WiringPi pin number)

#define BUTTON 12

MODULE_LICENSE("GPL");

/*
static int cam_driver_open(struct inode *inode, struct file *file)
{
    printk("[CAM_DRIVER] Open\n");
    return 0;
}

static int cam_driver_release(struct inode *inode, struct file *file)
{
    printk("[CAM_DRIVER] Release\n");
    return 0;
}

struct file_operations cam_driver_fops =
{
    .open = cam_driver_open,
    .release = cam_driver_release
};
*/

static int __init cam_driver_init(void)
{
    printk("[CAM_DRIVER] Init\n");

    // Init GPIO
    gpio_request_one(BUTTON, GPIOF_IN, "BUTTON");

    return 0;
}

static void __exit cam_driver exit(void)
{
    printk("[CAM_DRIVER] Exit\n");

    // Free GPIO
    gpio_free(BUTTON);
}

module_init(cam_driver_init);
module_exit(cam_driver_exit);
