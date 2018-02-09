#!/usr/bin/python

# Creator:   Ryan Mathews
# Purpose:   Tests the Logitech Webcam's ability to detect black lines
# Functions: Reads video images from webcam, converts RGB to HSV,
# 	     checks if pixel HSV color in preset bounds
#	     prints direction black line is detected
#	     prints "not centered" if center pixel strays from black line

import cv2
import numpy as np

lowBoundB=np.array([0,0,0])
upBoundB=np.array([360, 100, 15])

cam=cv2.VideoCapture(1)
kernelOpen=np.ones((5,5))
kernelClose=np.ones((20,20))

while True:
	ret, img=cam.read()

	imgHSV=cv2.cvtColor(img, cv2.COLOR_BGR2HSV)

	mask = cv2.inRange(imgHSV, lowBoundB, upBoundB)

	if mask[240,320] == 255:
		print "centered"
	#	print "not centered"
	#else print "centered"

	if mask[10,10]==255:
		print "top left"

	if mask[10,630]==255:
		print "top right"

	if mask[240,10]==255:
		print "left"

	if mask[240,630]==255:
		print "right"

	if mask[470,10]==255:
		print "bottom left"

	if mask[470,630]==255:
		print "bottom right"

	cv2.imshow("cam",img)

	if cv2.waitKey(1) == 27:
		break

cam.release()
cv2.destroyAllWindows()
