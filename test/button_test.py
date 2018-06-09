import time
import RPi.GPIO as GPIO

GPIO.setmode(GPIO.BCM)
GPIO.setup(27, GPIO.OUT)
GPIO.setup(23, GPIO.IN, pull_up_down=GPIO.PUD_UP)

print('Press the button')

try:
    while True:
        input_state = GPIO.input(23)

        if input_state == False:
            GPIO.output(27, GPIO.HIGH)
        else:
            GPIO.output(27, GPIO.LOW)
        time.sleep(1)
except KeyboardInterrupt:
GPIO.cleanup()
