#! /usr/bin/python

import os
import sys
import time
import shlex
import subprocess

from socket import *
# a simple TCP/IP server that terminates when it receives 'quit'

def runServer(ip_addr='', port=7000):
        addr = (ip_addr, port)

        sock = socket(AF_INET, SOCK_STREAM)

        try:
            sock.bind(addr)
        except Exception as ex:
            print("wait for a bit and try again")
            return

        print("listening on port %d" % (port))
        sock.listen(5)

        quit = False
        while not quit:
            client_sock, client_addr = sock.accept()
            print("accepted connection from %s:%d" % (client_addr[0], client_addr[1]))

            cmd = client_sock.recv(4096)
            print("%s" % (cmd.strip(' \n\r')))

            if cmd.strip().lower()[:4] == 'quit':
                quit = True
                out = 'quit\n'
            else:
                args = shlex.split(cmd)
                #print('args: %r' % (args))
                try:
                    child_proc = subprocess.Popen(args, stdin=None, stdout=subprocess.PIPE, stderr=subprocess.PIPE, universal_newlines=True)
                    out, err = child_proc.communicate()
                except :
                    out = 'Command not found.\n'


            response = out.strip()
            client_sock.sendall(response)
            client_sock.shutdown(SHUT_RDWR)
            client_sock.close()

        try:
            sock.shutdown(SHUT_RDWR)
        except:
            pass
        sock.close()


if __name__ == '__main__':
    runServer()

