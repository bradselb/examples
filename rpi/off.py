#! /usr/bin/python

from RPi import GPIO

led = 4
GPIO.setwarnings(False)

GPIO.setmode(GPIO.BCM)
GPIO.setup(led, GPIO.OUT)
GPIO.output(led, 0)
GPIO.cleanup()

