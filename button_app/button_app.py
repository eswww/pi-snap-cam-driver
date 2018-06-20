import os

dev = os.open('/dev/button_driver', os.O_RDWR)

count = 0
while count < 10:
    print(os.read(dev, 0))
    count += 1

os.close(dev)
