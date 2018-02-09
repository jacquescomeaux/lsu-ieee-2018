#!/usr/bin/python

# Creator: Ryan Mathews
# Purpose: Detect set colors and draw square around detected mask

# Each color tested seperately; others commented out during tests
# However, has the ability to detect all at the same time

import cv2
import numpy as np

# Green
lowerBoundG=np.array([33,80,40])
upperBoundG=np.array([102,255,255])

# Red
lowerBoundR=np.array([160,100,100])
upperBoundR=np.array([179,255,255])

# Blue
lowerBoundB=np.array([110,50,50])
upperBoundB=np.array([130,255,255])

# Yellow
lowerBoundY=np.array([25,50,50])
upperBoundY=np.array([32,255,255])

# Black
#lowerBoundBl=np.array([0,0,0)]
#upperBoundBl=np.array([0,0,10)]

# White
#lowerBoundW=np.array([0,0,200])
#upperBoundW=np.array([180,255,255])

# Grey
#lowerBoundGr=np.array([0,0,40])
#upperBoundGr=np.array([0,0,85])

cam=cv2.VideoCapture(1)
kernelOpen=np.ones((5,5))
kernelClose=np.ones((20,20))


def trackSquare( lowBound, upBound):
	mask = cv2.inRange( imgHSV, lowBound, upBound )

	maskOpen=cv2.morphologyEx( mask, cv2.MORPH_OPEN, kernelOpen )
	maskClose=cv2.morphologyEx( maskOpen, cv2.MORPH_CLOSE, kernelClose )

	maskFinal=maskClose
	_,conts,h=cv2.findContours( maskFinal.copy(), cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_NONE )

	cv2.drawContours(img,conts,-1,(255,0,0),3)
        for i in range(len(conts)):
                x,y,w,h=cv2.boundingRect(conts[i])
                cv2.rectangle(img,(x,y),(x+w,y+h),(0,0,255),2)

		# following lines returns coordinates of square contour trace
                #print(x)
                #print("::")
                #print(y)


while True:
	ret, img=cam.read()
	img=cv2.resize(img,(340,220))

	imgHSV=cv2.cvtColor( img, cv2.COLOR_BGR2HSV )

	trackSquare( lowerBoundG,  upperBoundG  )
        trackSquare( lowerBoundR,  upperBoundR  )
        trackSquare( lowerBoundY,  upperBoundY  )
        trackSquare( lowerBoundB,  upperBoundB  )
	#trackSquare( lowerBoundBl, upperBoundBl )
	#trackSquare( lowerBoundW,  upperBoundW  )
	#trackSquare( lowerBoundGr, upperBoundGr )

	#cv2.imshow("maskClose",maskClose)
	#cv2.imshow("maskOpen",maskOpen)
	#cv2.imshow("mask",mask)
	cv2.imshow("cam",img)
	cv2.waitKey(10)

	if cv2.waitKey(1) == 27:
		break

cam.release()
cv2.destroyAllWindows()
