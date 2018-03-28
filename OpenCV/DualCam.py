#!/usr/bin/python

import cv2
#import numpy as np

picam = cv2.VideoCapture(1)
#webcam = cv2.VideoCapture(1)

while True:
#	ret,  img=webcam.read()
	ret1, gmi=picam.read()

	imgHSV = cv2.cvtColor(gmi, cv2.COLOR_BGR2HSV)

#	cv2.imshow("webcam", img)
	cv2.imshow("picam", gmi)
	cv2.imshow("HSV", imgHSV)

	if cv2.waitKey(1) == 27:
		break

#webcam.release()
picam.release()
cv2.destroyAllWindows()
