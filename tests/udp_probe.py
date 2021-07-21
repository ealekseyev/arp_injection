import socket

UDP_IP = input("Destination IP: ")
UDP_PORT = int(input("UDP port: "))
sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
while True:
	MESSAGE = input("Payload: ")
	ptype = input("Payload type: ").lower().strip()
	if ptype == 'ascii' or ptype == 'char' or ptype == '26' or ptype == 'str':
		sock.sendto(bytes(MESSAGE, 'utf-8'), (UDP_IP, UDP_PORT))
	elif ptype == 'dec' or ptype == '10':
		sock.sendto(bytearray([int(i, 10) for i in MESSAGE.split(' ')]), (UDP_IP, UDP_PORT))
	elif ptype == 'hex' or ptype == '16':
		sock.sendto(bytearray([int(i, 16) for i in MESSAGE.split(' ')]), (UDP_IP, UDP_PORT))
	elif ptype == 'bin' or ptype == '2':
		sock.sendto(bytearray([int(i, 2) for i in MESSAGE.split(' ')]), (UDP_IP, UDP_PORT))
	else:
		quit()
	data, addr = sock.recvfrom(1024) # buffer size is 1024 bytes
	print("Received reply:\n%s" %(data))
