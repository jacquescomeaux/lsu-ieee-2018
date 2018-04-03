#!/usr/bin/python

import cv2
#import numpy as np

# picam = Raspberry Pi Camera Module
# webcam = Logitech c920

# Height: 480
# Width:  640

Y1=160
Y2=400
X1=195
X2=440

#picam = cv2.VideoCapture(0)
webcam = cv2.VideoCapture(0)

while True:
	ret,  img=webcam.read()

	cv2.imshow("picam", img)

	cv2.imwrite("Color.png", img)

	if cv2.waitKey(1) == 27:
		break
cv2.waitKey(10)

webcam.release()
#picam.release()
cv2.destroyAllWindows()
