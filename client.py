import socket
import sys
import random
import time

clientName = sys.argv[1].encode("utf-8")
min = int(sys.argv[2])
max = int(sys.argv[3])
delay = int(sys.argv[4])

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM, socket.IPPROTO_TCP)
s.connect(('127.0.0.1', 34220))
s.send(clientName)
data = s.recv(1024)
s.close()

time.sleep(1)

s2 = socket.socket(socket.AF_INET, socket.SOCK_STREAM, socket.IPPROTO_TCP)
s2.connect(('127.0.0.1', int(data.decode("utf-8"))))
while True:
    ran = str(random.randint(min, max)).encode("utf-8")
    s2.send(ran)
    data = str(s2.recv(1024)).strip()
    print("{} is sent".format(str(ran)))

    if data == 'GET':
        ran = str(random.randint(min, max)).encode("utf-8")
        s2.send(ran)
        print("{} is sent".format(str(ran)))
        data = s2.recv(1024)
    time.sleep(delay)
s.close()

