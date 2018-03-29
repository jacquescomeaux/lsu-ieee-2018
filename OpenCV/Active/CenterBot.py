#!/usr/bin/python

import numpy as np
import argparse
import cv2

cam = cv2.VideoCapture(1)

Y1=117
Y2=410
X1=195
X2=440

while True:

        ret, image=cam.read()

        cv2.imshow("original", image)

        #image=cv2.medianBlur(image,5)

	img=image[Y1:Y2, X1:X2]
        output=img.copy()
        gray=cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)

        # Hough Circle Transform
        # HoughCircles(src_gray,circles,CV_HOUGH_GRADIENT,1,min_dist,p1,p2,min_rad,max_rad)
        # ARGUMENTS
        # dp = 1 : the inverse ratio of resolution (increase for higher sensitivity)
        # min_dist : minimum distance between detected centers
        # p1 : upper threshold for internal canny edge detector
        # p2 : threshold for center detection
        # min_rad = 0 : minimym radius to be detected (default = 0)
        # max_rad = 0 : maximum radius to be detected (default = 0)
        circles=cv2.HoughCircles(gray,cv2.HOUGH_GRADIENT,1.5,300,5,80,40,55)

	#circles=cv2.HoughCircles(gray,cv2.HOUGH_GRADIENT,1.6,300)

        # Ensure at least some circles were found
        if circles is not None:

                # Convert the (x, y) coordinates and radius of the circles to integers
		circles = np.round(circles[0, :]).astype("int")
                #if (x is not None) and (y is not None) and (r is not None):
		# Loop over the (x, y) coordinates and radius of the circles
                try:
			for (x, y, r) in circles:

                        # Draw the circle in the output image, then draw a rectangle
                        # corresponding to the center of the circle
                        	cv2.circle(output, (x, y), r, (0, 255, 0), 4)
                        	cv2.rectangle(output, (x - 5, y - 5), (x + 5, y + 5), (0, 128, 255), -1)

			#print(x)
			#print(y)
		except:
			print('Value missing')
        # Show the output image
        #cv2.imshow("output", np.hstack([image, output]))
	cv2.imshow("imageCrop", img)
        cv2.imshow("output", output)

	if cv2.waitKey(1) == 27:
               break

cam.release()
cv2.destroyAllWindows()

