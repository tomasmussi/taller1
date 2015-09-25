
import socket;

def main():
	s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
	s.connect(("localhost", 1080))
	s.sendall("-1")
	s.sendall("a")
	s.shutdown(socket.SHUT_WR)
	data = s.recv(65535)
	s.close()
	total = len(data)
	for i in xrange(total):
		print (data[i]),
	
main()
