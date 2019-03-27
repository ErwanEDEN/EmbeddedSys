#!/usr/bin/python
#-*- coding: utf-8 -*-

import sys
import serial
import os
import time

ser = serial.Serial('/dev/ttyACM0' , 9600)
cmd1 = 'echo "L'eau bout!!" | mail -s "Alerte!" erwanzimmer@gmail.com'
cmd2 = 'echo "Trop de fumée" | mail -s "DANGER!" erwanzimmer@gmail.com'


while 1:
	var = ser.readline()
	if 'v10' in var > True :
		print("Hote allumée vitesse 1")
		os.system(cmd1)
	elif 'v20' in var > True :
		print("Hote allumée vitesse 2")
		os.system(cmd2)
	print(var);
	time.sleep(1)

