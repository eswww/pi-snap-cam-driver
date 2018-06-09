#include <stdio.h>
#include <unistd.h>
#include <sys/fcntl.h>

int main(void)
{
    char ch;
    int dev = open("/dev/button_driver", O_RDWR);
    if(dev < 0)
        return -1;

    scanf("%c", &ch);

    close(dev);
    return 0;
}
