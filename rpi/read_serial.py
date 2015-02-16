#! /usr/bin/python
import serial 
import time
import sys
import os

if len(sys.argv) > 1:
    filename = sys.argv[1]
else:
    filename = '%s.%s' % (time.strftime('%Y%m%d'), 'nmea')

if not os.path.exists(filename):
    f = open(filename, "w")
    f.close()

while True:
    with serial.Serial(port="/dev/ttyAMA0", baudrate=9600) as port:
        with open(filename, "a") as f:

            line_count = 0
            line = ""
            while line_count < 10:
                ch = port.read(1)

                if (ch != '\r'):
                    line += ch

                if (ch == '\n'):
                    if (0 == line.find("$GPGGA")) or (0 == line.find("$GPRMC")):
                        print(line)
                        f.write(line)
                        line_count += 1
                    line = ""


    time.sleep(30)

