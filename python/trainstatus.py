#!/usr/bin/python 
import sys
import time
import requests
import json
from operator import itemgetter


# The POST method does not work here so, use a GET instead.
base_url = 'http://acerail.com/CMSWebParts/ACERail/TrainStatusService.aspx'
get_vehicles_params = {'service':'get_vehicles'}
get_stops_params = {'service':'get_stops'}

r = requests.get(base_url, params=get_vehicles_params)
#d = json.loads(r.text)
d = r.json
vehicles = sorted(d['get_vehicles'], key=itemgetter('equipmentID'))
#print("vehicles is type: %s" % (type(vehicles)))
#print("%r" % (vehicles))

r = requests.get(base_url, params=get_stops_params)
stops = r.json




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

    print('%s, %.6f, % 11.6f , %s UTC' % (eid, lat, lon, timereceive))


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



