#include <linux/init.h>
#include <linux/module.h>
#include <linux/slab.h>
#include <linux/uaccess.h>
#include <linux/interrupt.h>
#include <linux/cdev.h>
#include <linux/fs.h>
#include <linux/kernel.h>
#include <linux/gpio.h>
#include <linux/wait.h>
#include <linux/sched.h>
#include <linux/delay.h>

#define DEV_NAME "button_driver"

#define BUTTON 26

MODULE_LICENSE("GPL");

dev_t dev_num;
static int irq_num;
static int button_status;
static struct cdev *cd_cdev;

wait_queue_head_t wq;
spinlock_t button_lock;

static int button_driver_open(struct inode *inode, struct file *file)
{
    printk("[BUTTON_DRIVER] Open\n");
    enable_irq(irq_num);
    return 0;
}

static int button_driver_release(struct inode *inode, struct file *file)
{
    printk("[BUTTON_DRIVER] Release\n");
    disable_irq(irq_num);
    return 0;
}

static int button_driver_read(struct file *file, char *buf, size_t len, loff_t *lof)
{
    // Blockin I/O
    wait_event_interruptible(wq, button_status != 0);

    spin_lock(&button_lock);
    button_status = 0;
    spin_unlock(&button_lock);

    return 0;
}

static irqreturn_t button_driver_isr(int irq, void *dev)
{
    printk("[BUTTON_DRIVER] Push\n");

    spin_lock(&button_lock);
    button_status = 1;
    spin_unlock(&button_lock);

    wake_up_interruptible(&wq);

    return IRQ_HANDLED;
}

struct file_operations button_driver_fops =
{
    .open = button_driver_open,
    .release = button_driver_release,
    .read = button_driver_read
};

static int __init button_driver_init(void)
{
    int ret;

    printk("[BUTTON_DRIVER] Init\n");

    button_status = 0;

    init_waitqueue_head(&wq);
    spin_lock_init(&button_lock);

    // Init dev
    alloc_chrdev_region(&dev_num, 0, 1, DEV_NAME);
    cd_cdev = cdev_alloc();
    cdev_init(cd_cdev, &button_driver_fops);
    cdev_add(cd_cdev, dev_num, 1);

    // Init GPIO
    gpio_request_one(BUTTON, GPIOF_IN, "button");
    irq_num = gpio_to_irq(BUTTON);

    // Init irq
    ret = request_irq(irq_num, button_driver_isr, IRQF_TRIGGER_RISING, "button_irq", NULL);
    if(ret)
    {
        printk(KERN_ERR "[BUTTON_DRIVER] Error - unable to request IRQ %d\n", ret);
        free_irq(irq_num, NULL);
    }
    else
        disable_irq(irq_num);

    return 0;
}

static void __exit button_driver_exit(void)
{
    printk("[BUTTON_DRIVER] Exit\n");

    // Free GPIO
    gpio_free(BUTTON);

    // Free irq
    free_irq(irq_num, NULL);

    // Free dev
    cdev_del(cd_cdev);
    unregister_chrdev_region(dev_num, 1);
}

module_init(button_driver_init);
module_exit(button_driver_exit);
