#! /usr/bin/python
import serial 
import time
import sys
import os

line = str()
with serial.Serial(port="/dev/ttyAMA0", baudrate=9600) as in_port:
    with serial.Serial(port="/dev/ttyACM0", baudrate=9600) as out_port:
        while True:
            ch = in_port.read()
            out_port.write(ch)

            if (ch is '$'):
                print(line)
                line = '$'
            else:
                line += ch


