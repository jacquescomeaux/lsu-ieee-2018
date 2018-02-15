#!/usr/bin/python

import cv2
import numpy as np

lowBoundB=np.array([0,0,0])
upBoundB=np.array([360, 100, 15])

cam=cv2.VideoCapture(1)
kernelOpen=np.ones((5,5))
kernelClose=np.ones((20,20))

def prepIntersect(tLeft, tMid, tRight):

	# load register with next instruction

	if tMid==255:
		return "Straight"
	elif tLeft==255:
		return "Left"
	else return "Right"

while True:
	ret, img=cam.read()

	imgHSV=cv2.cvtColor(img, cv2.COLOR_BGR2HSV)

	mask = cv2.inRange(imgHSV, lowBoundB, upBoundB)

	if mask[320,240] != 255:
		print "not centered"

	# interrupt needed for "not centered" if below statement true
	# prep for intersect will also include orientation & source pos
	## IF LEFT OR RIGHT LINE APPEARS
	if mask[320,240]==255 or mask[640,0]==255:
		prepIntersect(mask[10,10], mask[320,10], mask[630, 10])

	cv2.imshow("cam",img)

	if cv2.waitKey(1) == 27:
		break

cam.release()
cv2.destroyAllWindows()
