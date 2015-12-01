#!/usr/bin/python 
import time
import urllib2
import json
import sys
from operator import itemgetter

# The POST method does not work here so, use a GET instead.
base_url = 'http://acerail.com/CMSWebParts/ACERail/TrainStatusService.aspx'
get_vehicles_url = base_url + '?service=get_vehicles'
get_stops_url =  base_url + '?service=get_stops'

# fetch the info from ACE website / webservice
f = urllib2.urlopen(get_vehicles_url)
s = f.read()
if s and len(s):
    d = json.loads(s)
    vehicles = sorted(d['get_vehicles'], key=itemgetter('equipmentID'))
#    print ("%s" % vehicles)
else:
    print("Failed to load vehicles. Exiting.")
    sys.exit(1)

f = urllib2.urlopen(get_stops_url)
s = f.read()
if s and len(s):
    stops = json.loads(s)
#    print ("%s" % stops)
else:
    print("Failed to load stops. Exiting.")
    sys.exit(1)


# create a dictionary that maps stop id to name
stopName = dict()
for d in stops['get_stops']:
	stopName[d['id']] = d['name']


timeformat = '%Y-%m-%d %H:%M:%S'
timenow = time.strftime(timeformat)

print('')
for vehicle in vehicles:
    eid = vehicle.get('equipmentID', '?')
    lat = vehicle['lat']
    lon = vehicle['lng']
    receiveTime = vehicle['receiveTime']/1000 # seconds since epoc
    timereceive = time.strftime(timeformat, time.gmtime(receiveTime))

    print('%s' % (eid))
    print('%s UTC' % (timereceive))
    print('%.6f, %.6f' % (lat, lon))
    print('')


print('')
for vehicle in vehicles:
    inservice = vehicle['inService']
    n = vehicle['scheduleNumber']
    t = vehicle.get('onSchedule', 0)
    eid = vehicle.get('equipmentID', '?')
    if vehicle['inService']:
        print('%s' % (timenow))
        if (t == 0):
        	print('Train #%s (%s) is on time' % (n, eid))
        elif (t < 0):
        	print('Train #%s (%s) is %s minutes late' % (n, eid, -t))
        elif (t > 0):
        	print('Train #%s (%s) is %s minutes early' % (n, eid, t))
        else:
        	print('Train #%s (%s)' % (n, eid))

        for stop in vehicle[u'minutesToNextStops']:
        	if (stop['minutes'] != None):
        		print('  %s in %s minutes (%s)' % (stopName[stop['stopID']], stop['minutes'], stop['time']))
        print('\n')


