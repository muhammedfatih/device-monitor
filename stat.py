import socket
import sys
import random
import time

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM, socket.IPPROTO_TCP)
s.connect(('127.0.0.1', 34221))
s.send(b'stat')
data = s.recv(1024)
s.close()

print(data)