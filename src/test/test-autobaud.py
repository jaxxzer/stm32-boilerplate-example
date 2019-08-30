#!/usr/bin/env python3

import serial

s = serial.Serial("/dev/ttyUSB0")
s.timeout = 1

baudrates = [
    4800,
    9600,
    19200,
    38400,
    57600,
    115200,
    230400,
    460800,
    921600,
    1000000,
    2000000,
    2500000]

for baudrate in baudrates:
    print("testing baudrate %d" % baudrate)
    s.baudrate = baudrate
    s.send_break()
    s.write("U".encode())
    s.write("hello world!".encode())
    print(s.read(14))
