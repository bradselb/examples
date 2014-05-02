# this is a quick & dirty script that captures broadcast datagrams 
# and prints out the hexadecimal representation of the bytes received.
import sys
from socket import *
sock = socket(AF_INET, SOCK_DGRAM)
sock.bind(('', 9000)) # any address, port 9000
try:
    while True:
        s = sock.recv(4096)
        for c in s:
            hexstr = '{:02x}'.format(ord(c))
            sys.stdout.write(hexstr)

        sys.stdout.flush()

except KeyboardInterrupt as e:
    pass

print('')

