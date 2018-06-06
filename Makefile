KDIR := ~/linux-rpi
ARM := ARCH=arm CROSS_COMPILE=arm-linux-gnueabi-
PWD := $(shell pwd)

obj-m := light_driver.o

default:
	$(MAKE) -C $(KDIR) M=$(PWD) $(ARM) modules

copy:
	scp light_driver.ko  pi@10.10.10.13:~
clean:
	$(MAKE) -C $(KDIR) M=$(PWD) $(ARM) clean

