import sys
import time
from time import sleep

SYSFS_GPIO_DIR = '/sys/class/gpio'

HIGH = "HIGH"
LOW = "LOW"
OUTPUT = "OUTPUT"
INPUT = "INPUT"
MAX_BUF = 64
#gpio number == 18

dev = file('/dev/button_driver', 'r')
if dev<0:
	print("open error")

fd = file(SYSFS_GPIO_DIR+'/export','r')

if fd<0:
	print('Can not export gpio ')



#inData = fw.read()


for i in range(0,9):
	filename = SYSFS_GPIO_DIR+'/gpio18/value'
	fw = file(filename,"r") #open the pin's value file for reading	
	inData = fw.read()
	fw.close()
	if inData == '0':
		print(LOW)
	else:
		print(HIGH)
	sleep(1)