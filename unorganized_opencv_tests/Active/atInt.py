#!/usr/bin/python

import cv2
import numpy as np
#58800
cam = cv2.VideoCapture(1)

Y1=160
Y2=400
X1=195
X2=440

while True:
	e1 = cv2.getTickCount() #for testing code efficiency
	ret, img = cam.read()

	img = img[Y1:Y2, X1:X2]

	img = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)

	#img = cv2.resize(img, (340, 220, 1))

	nW = cv2.countNonZero(img)
        e2 = cv2.getTickCount()
        t = (e2 - e1)/cv2.getTickFrequency() #calculates num secs to complete loop iteration

	print (t)
	print(nW)

cam.release()
