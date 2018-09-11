#!/usr/bin/python

import numpy as np
import argparse
import cv2

cam = cv2.VideoCapture(1)

kernel = np.ones((5,5),np.uint8)

Y1=117
Y2=400
X1=195
X2=440

pts1 = np.float32([[92,0],[148,0],[74,283],[178,283]])
pts2 = np.float32([[74,0],[140,0],[74,283],[140,283]])

while True:

        ret, image=cam.read()

        #cv2.imshow("original", image)

        #im=cv2.bilateralFilter(image,15,200,200)
        #ret, thresh = cv2.threshold(image,100,255,cv2.THRESH_BINARY)

        img=image[Y1:Y2, X1:X2]
        #dilation = cv2.dilate(img, kernel, iterations=1)
        #erosion = cv2.erode(dilation, kernel, iterations = 1)
        #img=cv2.morphologyEx(img, cv2.MORPH_GRADIENT, kernel)

        M = cv2.getPerspectiveTransform(pts1,pts2)

        dst = cv2.warpPerspective(img, M,(245,283))

        output=dst.copy()
        gray=cv2.cvtColor(output, cv2.COLOR_BGR2GRAY)
        gray=cv2.bilateralFilter(gray, 9, 75, 75)
        #ret, gray = cv2.threshold(gray, 80, 255, cv2.THRESH_BINARY)
        #gray=cv2.dilate(gray, kernel, iterations=1)
        #gray=cv2.morphologyEx(gray, cv2.MORPH_GRADIENT, kernel)
        #gray=cv2.dilate(gray, kernel, iterations=1)
        #gray=cv2.morphologyEx(gray, cv2.MORPH_OPEN, kernel)
        #gray=cv2.bilateralFilter(gray,9,75,75)
        gray=cv2.Canny(gray,50,100)
        #cv2.Smooth(output, output, cv2.CV_GAUSSIAN,7 ,7)
        #erosion = cv2.erode(gray, kernel, iterations = 5)
        #dilation = cv2.dilate(erosion, kernel, iterations = 5)

        # Hough Circle Transform
        # HoughCircles(src_gray,circles,CV_HOUGH_GRADIENT,1,min_dist,p1,p2,min_$
        # ARGUMENTS
        # dp = 1 : the inverse ratio of resolution (increase for higher sensiti$
        # min_dist : minimum distance between detected centers
        # p1 : upper threshold for internal canny edge detector
        # p2 : threshold for center detection
        # min_rad = 0 : minimym radius to be detected (default = 0)
        # max_rad = 0 : maximum radius to be detected (default = 0)
        circles=cv2.HoughCircles(gray,cv2.HOUGH_GRADIENT,2,300,100,200,40,55)

        #circles=cv2.HoughCircles(gray,cv2.HOUGH_GRADIENT,2,300)

        # Ensure at least some circles were found
        if circles is not None:

                # Convert the (x, y) coordinates and radius of the circles to i$
                circles = np.round(circles[0, :]).astype("int")

                # Loop over the (x, y) coordinates and radius of the circles
                try:
                        for (x, y, r) in circles:

                                # corresponding to the center of the circle
                                cv2.circle(output, (x, y), r, (0, 255, 0), 4)
                                cv2.rectangle(output, (x - 5, y - 5), (x + 5, y))
                                print('X')
                                print(x)
                                print('Y')
                                print(y)

                except: print('No Circle')
        # Show the output image
        #cv2.imshow("output", np.hstack([image, output]))
        cv2.imshow("imageCrop", img)
        cv2.imshow("output", output)
        cv2.imshow("dilation",gray)

        if cv2.waitKey(1) == 27:
               break

cam.release()
cv2.destroyAllWindows()

