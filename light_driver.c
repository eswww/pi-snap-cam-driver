#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/gpio.h>
#include <linux/delay.h>

#define DEV_NAME "light_driver"

#define LIGHT 21

#define LOW 0
#define HIGH 1

MODULE_LICENSE("GPL");


void light_sensor(void){

	int cur_val;
	cur_val = gpio_get_value(LIGHT);
	printk("cur_val : %d\n",cur_val);
	
}

static int __init light_driver_init(void)
{
	printk("[LIGHT_DRIVER] Init\n");
	gpio_request_one(LIGHT, GPIOF_IN, "LIGHT");

	/* 0 - dark , 1 - light */

	int i;
	for(i = 0 ; i < 10; i++){
		light_sensor();
		mdelay(100);
	}
	
	return 0;	
}

static void __exit light_driver_exit(void)
{	
	printk("[LIGHT_DRIVER] Exit\n");
	gpio_free(LIGHT);
}

module_init(light_driver_init);
module_exit(light_driver_exit);
