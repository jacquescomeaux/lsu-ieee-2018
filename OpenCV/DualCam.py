#!/usr/bin/python

import cv2
#import numpy as np

# picam = Raspberry Pi Camera Module
# webcam = Logitech c920
#X1=260
#X2=300
#Y1=200
#Y2=400

Y1=160
Y2=400
X1=195
X2=440

#picam = cv2.VideoCapture(0)
webcam = cv2.VideoCapture(2)

#480, 220-260
#640, 360-520
#3

#Y1=160
#Y2=400
#X1=195
#X2=440


while True:
	ret,  img=webcam.read()
#	ret1, gmi=picam.read()

#	imgHSV = cv2.cvtColor(img, cv2.COLOR_BGR2HSV)
	img = img[Y1:Y2, X1:X2]
	height,width,depth=img.shape
	#print(height)
	#print(width)
	#print(depth)

#	cv2.imshow("webcam", img)
	cv2.imshow("picam", img)
#	cv2.imshow("HSV", imgHSV)

	if cv2.waitKey(1) == 27:
		break
cv2.waitKey(10)

webcam.release()
#picam.release()
cv2.destroyAllWindows()
