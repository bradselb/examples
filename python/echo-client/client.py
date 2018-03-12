import socket


class TestClient:
	def __init__(self, target_addr, tcp_port=7000, my_ip_addr=0, *args, **kwargs):
		self.target_addr = (target_addr, tcp_port)
		self.source_addr = (my_ip_addr, 0)


	def sendCommandLine(self, cmdline):
		"""
		This function connected to a TCP Server runnin gon the target and 
		together, this client-server pair act like a very primative remote
		shell. 

		Send the command line to the target and receive whatever is written to 
		stdout by the remote process.  
		"""

		# TODO: barf if fed garbage.


		sock = socket.create_connection(self.target_addr, timeout=10)

		sock.sendall(cmdline)
		response = sock.recv(4096)
		sock.shutdown(socket.SHUT_RDWR)
		sock.close()

		return response

if __name__ == '__main__' :
    myClient = TestClient('localhost')
    for cmd in ('uname -nrv', 'ls -l /etc', 'who', 'ping -c 5 tanagra'):
        s = myClient.sendCommandLine("%s\n" % (cmd))
        print s


