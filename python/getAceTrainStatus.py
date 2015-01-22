#!/usr/bin/python 
import time
import urllib2
import json


# The POST method does not work here so, use a GET instead.
base_url = 'http://acerail.com/CMSWebParts/ACERail/TrainStatusService.aspx'
get_vehicles_url = base_url + '?service=get_vehicles'
get_stops_url =  base_url + '?service=get_stops'
# print(get_vehicles_url)

# fetch the info from ACE website / webservice
f = urllib2.urlopen(get_vehicles_url)
s = f.read()
vehicles = json.loads(s)

f = urllib2.urlopen(get_stops_url)
s = f.read()
stops = json.loads(s)

f.close()

#print ("%s" % stops)
#print ("%s" % vehicles)


# create a dictionary that maps stop id to name
stopName = dict()
for d in stops['get_stops']:
	stopName[d['id']] = d['name']


timeformat = '%Y-%m-%d %H:%M:%S'
timestamp = time.strftime(timeformat)

print('')
for vehicle in vehicles['get_vehicles']:
    if vehicle['inService']:
        print('%s' % timestamp)

        n = vehicle['scheduleNumber']
        t = vehicle['onSchedule']
        if (t ==0):
        	print('Train #%s is on time' % n)
        elif (t < 0):
        	print('Train #%s is %s minutes late' % (n, -t))
        elif (t > 0):
        	print('Train #%s is %s minutes early' % (n, t))
        else:
        	print('Train #%s' % n)        	

        eid = vehicle['equipmentID']
        receiveTime = vehicle['receiveTime'] / 1000 # seconds since epoc
        tm = time.strftime(timeformat, time.gmtime(receiveTime))
        print('%s UTC, %s, %s, %s' % (tm, eid, vehicle['lat'], vehicle['lng']))

        for stop in vehicle[u'minutesToNextStops']:
        	if (stop['minutes'] != None):
        		print('\t%s in %s minutes (%s)' % (stopName[stop['stopID']], stop['minutes'], stop['time']))
        print('\n')


