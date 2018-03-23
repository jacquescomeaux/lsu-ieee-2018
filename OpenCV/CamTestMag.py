#!/usr/bin/python

import cv2
#import numpy as np

picam = cv2.VideoCapture(0)

while True:
        ret,  img=picam.read()
	#img=cv2.resize(img,(340,220))

        cv2.imshow("picam", img)

#	waitKey();

        if cv2.waitKey(1) == 27:
                break

picam.release()
cv2.releaseAllWindows()
