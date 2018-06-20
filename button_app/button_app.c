#include <stdio.h>
#include <unistd.h>
#include <sys/fcntl.h>

int main(void)
{
    int d;
    int dev = open("/dev/button_driver", O_RDWR);
    if(dev < 0)
        return -1;

    while(1)
    {
        d = read(dev, NULL, 0);
        printf("push %d\n", d);
    }

    close(dev);
    return 0;
}
