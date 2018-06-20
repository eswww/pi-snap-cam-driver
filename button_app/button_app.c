#include <stdio.h>
#include <unistd.h>
#include <sys/fcntl.h>

int main(void)
{
    int dev = open("/dev/button_driver", O_RDWR);
    if(dev < 0)
        return -1;

    while(1)
        printf("Push %d\n", (int)read(dev, NULL, 0));

    close(dev);
    return 0;
}
