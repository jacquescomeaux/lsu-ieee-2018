#!/usr/bin/python

import cv2
#import numpy as np

# picam = Raspberry Pi Camera Module
# webcam = Logitech c920

#picam = cv2.VideoCapture(0)
webcam = cv2.VideoCapture(1)

#480, 220-260
#640, 360-520
#3

while True:
	ret,  img=webcam.read()
#	ret1, gmi=picam.read()

	imgHSV = cv2.cvtColor(img, cv2.COLOR_BGR2HSV)

	height,width,depth=img.shape
	#print(height)
	#print(width)
	#print(depth)

#	cv2.imshow("webcam", img)
	cv2.imshow("picam", img)
	cv2.imshow("HSV", imgHSV)

	if cv2.waitKey(1) == 27:
		break

webcam.release()
#picam.release()
cv2.destroyAllWindows()
