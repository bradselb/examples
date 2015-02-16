#! /usr/bin/python
import serial 
import time 

while True:
    port = serial.Serial(port="/dev/ttyAMA0", baudrate=9600)

    line_count = 0
    line = ""
    while line_count < 10:
        ch = port.read(1)

        if (ch != '\r' and ch != '\n'):
            line += ch

        if (ch == '\n'):
            if (0 == line.find("$GPGGA")) or (0 == line.find("$GPRMC")):
                print(line)
                line_count += 1
            line = ""

    port.close()
    time.sleep(30)

