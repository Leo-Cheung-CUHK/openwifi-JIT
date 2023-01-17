#!/usr/bin/env python3
# -*- coding: utf-8 -*-
import socket
import os

HOST = '192.168.13.1'
PORT = 9999

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect((HOST, PORT))

indata = s.recv(1024)
print('My ID is ' + indata.decode())

indata = s.recv(1024)
numbers = list(map(int, indata.split()))
print('Indexs for session 1')
print(numbers)
STAResource = numbers

indata = s.recv(1024)
numbers = list(map(int, indata.split()))
print('Indexs for session 2')
print(numbers)
STAResource1 = numbers

indata = s.recv(1024)
if len(indata) == 0: # connection closed
    s.close()
    print('server closed connection.')

binary_vec = [0]*10

index = 0
index_1 = 0

for binary_index in range (0,len(binary_vec)):
    if binary_index < 6:
        if (index < len(STAResource)):
            if (binary_index == STAResource[index]):
                binary_vec[binary_index] = 1
                index = index + 1
    else:
        if (index_1 < len(STAResource1)):
            if (binary_index == STAResource1[index_1]+6):
                binary_vec[binary_index] = 1
                index_1 = index_1 + 1
binary_vec.reverse()

print(binary_vec)
integer_out = 0
for bit in binary_vec:
    integer_out = (integer_out << 1) | bit
print(integer_out)

print("My assigned time slots")

binary_vec.reverse()
for i in range(len(binary_vec)):
    if i < 6:
        if i==0:
            print("Session 1: ")
        print("| ",end ="")
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
