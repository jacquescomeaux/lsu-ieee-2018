#!/usr/bin/env python

# Creator: Ryan Mathews
# Purpose: Test ability of Logitech Webcam to capture video

# Other Functions ---
#	   Masks image based on colors set in boundaries
#	   Opens windows showing original and masked image

from __future__ import print_function
import sys
import cv2
import numpy as np
import argparse
import cv2


boundaries = [
	([17, 15, 100], [50, 56, 200]),
	([86, 31, 4], [220, 88, 50]),
	([25, 146, 190], [62, 174, 25])
]


def main(argv):
	cap = cv2.VideoCapture(0)

	while True:
		ret, img = cap.read()
		cv2.imshow("input", img)

		key = cv2.waitKey(10)
		if key == 27:
			break

		for (lower, upper) in boundaries:
			lower = np.array(lower, dtype = "uint8")
			upper = np.array(upper, dtype = "uint8")

			mask = cv2.inRange(img, lower, upper)
			output = cv2.bitwise_and(img, img, mask = mask)

			cv2.imshow("images", np.hstack([img, output]))
			cv2.waitKey(1)

	#cap.release()
	#cap.open(0)
	cv2.destroyAllWindows()
	cv2.VideoCapture(0).release()

if __name__ == '__main__':
	main(sys.argv)
