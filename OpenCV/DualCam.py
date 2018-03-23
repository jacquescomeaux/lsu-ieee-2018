#!/usr/bin/python

import cv2
#import numpy as np

# picam = Raspberry Pi Camera Module
# webcam = Logitech c920

picam = cv2.VideoCapture(0)
webcam = cv2.VideoCapture(1)

while True:
	ret,  img=webcam.read()
	ret1, gmi=picam.read()

	cv2.imshow("webcam", img)
	cv2.imshow("picam", gmi)

	if cv2.waitKey(1) == 27:
		break

webcam.release()
picam.release()
cv2.destroyAllWindows()
