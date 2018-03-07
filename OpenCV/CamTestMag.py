#!/usr/bin/python

import cv2
#import numpy as np

picam = cv2.VideoCapture(0)

while True:
        ret,  img=picam.read()

        cv2.imshow("picam", img)

	waitKey();

        if cv2.waitKey(1) == 27:
                break

webcam.release()

