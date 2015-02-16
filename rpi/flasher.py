#! /usr/bin/python

import time
from RPi import GPIO

led = 4

GPIO.setmode(GPIO.BCM)
GPIO.setup(led, GPIO.OUT)

for i in range(86400):
	GPIO.output(led, 1)
	time.sleep(0.500)
	GPIO.output(led, 0)
	time.sleep(0.500)

GPIO.cleanup()

