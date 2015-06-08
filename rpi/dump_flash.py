#! /usr/bin/python
import serial 
import time
import sys
import os

PORT = '/dev/ttyUSB0'
BAUD = 57600


if len(sys.argv) > 1:
    filename = sys.argv[1]
else:
    filename = '%s.%s' % (time.strftime('%Y%m%d'), 'nmea')

if not os.path.exists(filename):
    f = open(filename, "w")
    f.close()

with serial.Serial(port=PORT, baudrate=BAUD, timeout=1) as port:
    with open(filename, "a") as f:
        time.sleep(5)

        reply = ""
        while len(reply) < 10:
            port.write('?')
            reply = port.read(100)
        print(reply)

        port.write('p')
        page = " "
        while len(page) > 0:
            page = port.read(256)
            f.write(page)
