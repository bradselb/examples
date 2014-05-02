#!/usr/bin/python 
import time
import urllib2
import json


# The POST method does not work here so, use a GET instead.
base_url = 'http://acerail.com/CMSWebParts/ACERail/TrainStatusService.aspx'
get_vehicles_url = base_url + '?service=get_vehicles'
get_stops_url =  base_url + '?service=get_stops'
# print(get_vehicles_url)

f = urllib2.urlopen(get_vehicles_url)
s = f.read()
f.close()

#print(s)

vehicles = json.loads(s)

timestamp = time.strftime('%Y-%m-%d %H:%M:%S')

for vehicle in vehicles['get_vehicles']:
    if vehicle['inService']:
        print('%s' % timestamp)
        for vkey in vehicle:
            if (vkey == u'minutesToNextStops'):
                # print type(vehicle[vkey]) # this is a list of dictionary
                for d in vehicle[vkey]:
                    # print d
                    if (d['minutes'] != None):
                        for mkey in d:
                            print('%s: %s' % (mkey, d[mkey]))
            else:
                print('%s: %s' % (vkey, vehicle[vkey]))
        print('\n')

