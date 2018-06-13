#include <stdio.h>
#include <unistd.h>
#include <sys/fcntl.h>
#include <errno.h>
#include <stdlib.h>

#define GPIO_INPUT 1
 #define GPIO_HIGH  1
 #define GPIO_LOW  0
 
 #define GPIO_NONE  "none"
 #define GPIO_FALLING "falling"
 #define GPIO_RISING "rising"
 #define GPIO_BOTH  "both"
 
 #define SYSFS_GPIO_DIR "/sys/class/gpio"
 
 #define MAX_BUF 64

int gpio_get_val(unsigned int gpio, unsigned int *val);

int main(void)
{
    char ch;
    unsigned int gpio;
    unsigned int val;
    char buf[MAX_BUF];
    int fd,len;
    int dev = open("/dev/button_driver", O_RDWR);
    if(dev < 0)
        return -1;
    //get gpio_export info --> /sys/class/export  gpio#num 
	fd = open(SYSFS_GPIO_DIR "/export", O_WRONLY);
 
     if (fd < 0) {
         fprintf(stderr, "Can't export GPIO %d pin: %s\n", gpio, strerror(errno));
         return fd;
     }
 
     len = snprintf(buf, sizeof(buf), "%d", gpio);
     write(fd, buf, len);
     close(fd);

    for(int i=10; i>=0; i--) {
    	gpio_get_val(18,&val);
    	printf("v : %d\n",val);
    	sleep(3);
    }

    close(dev);
    return 0;
}

int gpio_get_val(unsigned int gpio, unsigned int *val)
 {
     int fd, len;
     char buf[MAX_BUF];
 	//get value from /sys/class/export  gpio#num , 
     len = snprintf(buf, sizeof(buf), SYSFS_GPIO_DIR "/gpio%d/value", gpio);
 
     fd = open(buf, O_RDONLY);
 
     if (fd < 0) {
         fprintf(stderr, "Can't get GPIO %d pin value: %s\n", gpio, strerror(errno));
         return fd;
     }
 
     read(fd, buf, 1);
     close(fd);
 
     if (*buf != '0')
         *val = GPIO_HIGH;
     else
         *val = GPIO_LOW;
 
     return val;
 }
