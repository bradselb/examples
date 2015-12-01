import time
import requests

url = 'http://api.sunrise-sunset.org/json'
params = {'lat': 37.65842, 'lng': -121.88225, 'formatted': 0}

r = requests.get(url, params=params)
if (r.status_code == 200):
    d = r.json

    t = d['results']['sunrise'].split('+')[0] + ' UTC'

    ts = time.strptime(t, '%Y-%m-%dT%H:%M:%S %Z')

    if ts.tm_isdst==1:
        ts_local = time.localtime(time.mktime(ts) - time.altzone)
    else:
        ts_local = time.localtime(time.mktime(ts) - time.timezone)

    print("sunrise at: %s" % time.strftime("%I:%M:%S %p", ts_local))

    t = d['results']['sunset'].split('+')[0] + ' UTC'

    ts = time.strptime(t, '%Y-%m-%dT%H:%M:%S %Z')

    if ts.tm_isdst==1:
        ts_local = time.localtime(time.mktime(ts) - time.altzone)
    else:
        ts_local = time.localtime(time.mktime(ts) - time.timezone)

    print(" sunset at: %s" % time.strftime("%I:%M:%S %p", ts_local))

