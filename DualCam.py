#!/usr/bin/python

import cv2
import numpy as np

webcam = cv2.VideoCapture(1)
picam =  cv2.VideoCapture(0)

while True:
	ret,  img=webcam.read()
	ret1, gmi=picam.read()

	cv2.imshow("webcam", webcam)
	cv2.imshow("picam", picam)

	if cv2.waitKey(1) == 27;
		break

webcam.release()
picam.release()
cv2.destroyAllWindows()
