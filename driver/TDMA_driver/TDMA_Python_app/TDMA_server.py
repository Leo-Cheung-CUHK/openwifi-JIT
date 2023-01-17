#!/usr/bin/env python3
# -*- coding: utf-8 -*-
import socket
import fcntl
import struct
from random import randrange
import time
import os

def get_ip_address(ifname):
    s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    return socket.inet_ntoa(fcntl.ioctl(s.fileno(),0x8915,struct.pack('256s', ifname[:15]))[20:24])

# TDMA SYSTEM INFO
nodesInfo = {}

STAsResource = {}
STAsResource1 = {}

print('Welcome')
print('Start to set up this TDMA system!')
print('We have 10 slots in total. 6 slots for session 1 and 4 slots for session 2')

print('For AP')

s = input('please input the slot indexs for session 1:')
numbers = list(map(int, s.split()))
print(numbers)
APResource = numbers

s = input('please input the slot indexs for session 2:')
numbers = list(map(int, s.split()))
print(numbers)
APResource1 = numbers

binary_vec = [0]*10

index = 0
index_1 = 0

for binary_index in range (0,len(binary_vec)):
    if binary_index < 6:
        if (index < len(APResource)):
            if (binary_index == APResource[index]):
                binary_vec[binary_index] = 1
                index = index + 1
    else:
        if (index_1 < len(APResource1)):
            if (binary_index == APResource1[index_1]+6):
                binary_vec[binary_index] = 1
                index_1 = index_1 + 1
binary_vec.reverse()

print(binary_vec)
integer_out = 0
for bit in binary_vec:
    integer_out = (integer_out << 1) | bit
print(integer_out)

print("AP's assigned time slots")

binary_vec.reverse()
for i in range(len(binary_vec)):
    if i <= 19:
        if i==0:
            print("Session 1: ")
        print("| ",end =" ")
        if binary_vec[i] == 1:
            print("* |", end ="")
        else:
            print("_ |", end ="")
        if i== 5:
            print("|")
    else:
        if i == 6:
            print("Session 2: ")
        print("| ",end =" ")
        if binary_vec[i] == 1:
            print("* |", end ="")
        else:
            print("_ |", end ="")

        if i==9:
            print("|")

os.system("./userapp /dev/my_misc 1 "+ str(0)+" "+str(integer_out))

outdata = input('Please input the number of clients:')
nodesNumMax = int(outdata)
for node_index in range(0,nodesNumMax):
    print('For the '+str(node_index)+'-th client, ')
    s = input('please input the slot indexs for session 1:')
    numbers = list(map(int, s.split()))
    print(numbers)

    STAsResource[str(node_index)] = numbers

    s = input('please input the slot indexs for session 2:')
    numbers = list(map(int, s.split()))
    print(numbers)

    STAsResource1[str(node_index)] = numbers

# HOST = get_ip_address('sdr0')
HOST = '192.168.13.1'
PORT = 9999

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
s.bind((HOST, PORT))
s.listen(5)

print('server start at: %s:%s' % (HOST, PORT))
print('wait for connection...')

while True:
    conn, addr = s.accept()
    print('connected by a node with IP: ' + str(addr[0])+ ' at port:'+str(addr[1]))
    
    # add this node to dict
    this_node_ID = randrange(nodesNumMax)
    nodesInfo[str(this_node_ID)] = str(addr[0])

    outdata = str(this_node_ID)
    conn.send(outdata.encode())

    time.sleep(0.1)

    outdata = ' '.join(str(e) for e in STAsResource[str(this_node_ID)])
    conn.send(outdata.encode())

    time.sleep(0.1)

    outdata = ' '.join(str(e) for e in STAsResource1[str(this_node_ID)])
    conn.send(outdata.encode())

    time.sleep(0.1)

    conn.close()
