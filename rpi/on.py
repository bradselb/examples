#! /usr/bin/python

import time
from RPi import GPIO

led = 4

GPIO.setmode(GPIO.BCM)
GPIO.setup(led, GPIO.OUT)
GPIO.output(led, 1)
#time.sleep(1)
#GPIO.cleanup()

