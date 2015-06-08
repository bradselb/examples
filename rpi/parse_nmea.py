#! /usr/bin/python
import time
import sys
import os

filename = sys.argv[1]
#os.environ['TZ'] = 'US/Pacific'
#time.tzset()

messages = []
with open(filename, "r") as f:
    messages = f.readlines()


for msg in messages: 
    tokens = msg.split(",")
    if (tokens[0] == '$GPRMC'):
        hms = tokens[1]
        dmy = tokens[9]
        ts = "%s %s UTC" % (dmy, hms[:6])

        tm = time.strptime(ts, "%d%m%y %H%M%S %Z")
        # print("%s  %s" % (ts,tm))
        
        time_stamp = time.strftime("%H:%M:%S  %d-%b-%Y", tm)

        fix_type = tokens[2]

        idx = tokens[3].find('.')  -2
        lat = float(tokens[3][:idx]) + float(tokens[3][idx:])/60.0
        if tokens[4] == 'S':
            lat *= -1.0

        idx = tokens[5].find('.')  -2
        lon = float(tokens[5][:idx]) + float(tokens[5][idx:])/60.0
        if tokens[6] == 'W':
            lon *= -1.0

        speed = float(tokens[7]) * 1.852 # convert knots to kph
        course = float(tokens[8])

        print("%s   %f, %f  %6.1f degrees, %6.1f kph" % (time_stamp, lat, lon, course, speed))


