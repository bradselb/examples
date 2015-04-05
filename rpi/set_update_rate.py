#! /usr/bin/python
import serial 
import time
import sys
import os


def checksum (s):
    cksum = 0
    for ch in msg:
        cksum ^= ord(ch)
    return cksum


# this message selects all but, I don't see GSV ?
# 0:GLL, 1:RMC, 2:VTG, 3:GGA, 4:GSA, 5:GSV, 6..17:rsvd, 18:chan status
msg = "PMTK314,1,1,1,1,5,5,0,0,0,0,0,0,0,0,0,0,0,0,0"

# this message selects only the GGA and RMC sentences
#msg = "PMTK314,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0"
cksum = checksum(msg)
s1 = "%c%s*%02x\r\n" %  ('$', msg, cksum)
print("%s" % s1),

# set update rate to once per ten seconds (10000 milli-seconds)
#msg = "PMTK220,10000"
# set update rate to once per second (1000 milli-seconds)
msg = "PMTK220,1000"
cksum = checksum(msg)
s2 = "%c%s*%02x\r\n" %  ('$', msg, cksum)
print("%s" % s2)


with serial.Serial(port="/dev/ttyAMA0", baudrate=9600) as port:
    port.write(s1)
    port.write(s2)


