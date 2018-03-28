#!/usr/bin/python

import cv2
import sys
import numpy as np

cam = cv2.VideoCapture(1)

params = cv2.SimpleBlobDetector_Params()

params.minThreshold = 1
params.maxThreshold = 200

params.filterByArea = True
params.minArea = 100

params.filterByCircularity = True
params.minCircularity = 0.1

params.filterByConvexity = True
params.minCircularity = 0.1

params.filterByInertia = True
params.minInertiaRatio = 0.01

# Detector
ver = (cv2.__version__).split('.')
if int(ver[0]) < 3 :
	detector = cv2.SimpleBlobDetector(params)
else:
        detector = cv2.SimpleBlobDetector_create(params)


while True:

        ret, img = cam.read()

	imgHSV = cv2.cvtColor(img, cv2.COLOR_BGR2HSV)
	imgGray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)

        keypoints = detector.detect(img)

        img_w_keypoints = cv2.drawKeypoints(img, keypoints, np.array([]), (0,0,255), cv2.DRAW_MATCHES_FLAGS_DRAW_RICH_KEYPOINTS)

        cv2.imshow("Keypoints", img_w_keypoints)
	cv2.imshow("HSV", imgHSV)
	cv2.imshow("Gray", imgGray)
        #cv2.waitKey(0)

        if cv2.waitKey(1) == 27:
                break

cam.release()
cv2.destroyAllWindows()

