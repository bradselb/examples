#!/usr/bin/python 
import subprocess 

for i in range(1, 255):
	ipaddr = "192.168.117.%s" % (i)
	l = ["ping", "-q", "-c 3", ipaddr]
	rc = subprocess.call(l)
	if (rc == 0):
		s = "%s\n" % (ipaddr)
		with open("active", "a") as f:
			f.write(s)


