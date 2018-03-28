#!/usr/bin/python

# Creator: Ryan Mathews
# Purpose: Center over intersection

import cv2
import numpy as np

# Grey: RGB Upper and Lower Limits
lowerBoundG=np.array([0,0,0])
upperBoundG=np.array([40,40,40])

# Cropping Boundaries
Y1=165
Y2=410
X1=195
X2=440

cam=cv2.VideoCapture(1)
kernelOpen=np.ones((5,5))
kernelClose=np.ones((20,20))


def trackSquare( lowBound, upBound):
	mask = cv2.inRange( imgCrop, lowBound, upBound )

	maskOpen=cv2.morphologyEx( mask, cv2.MORPH_OPEN, kernelOpen )
	maskClose=cv2.morphologyEx( maskOpen, cv2.MORPH_CLOSE, kernelClose )

	maskFinal=maskClose
	_,conts,h=cv2.findContours( maskFinal.copy(), cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_NONE )

	#cv2.drawContours(img,conts,-1,(255,0,0),3)
	if conts:
        	#for i in range(len(conts)):
                	#x,y,w,h=cv2.boundingRect(conts[i])
                	#cv2.rectangle(img,(x,y),(x+w,y+h),(0,0,255),2)
	  cnt = conts[0]
	  M = cv2.moments(cnt)
	  cx = int(M['m10']/M['m00'])
	  cy = int(M['m01']/M['m00'])

	  print('Calculated from Moments')
	  print('cx')
	  print(cx)
	  print('cy')
	  print(cy)

	  (x,y),radius = cv2.minEnclosingCircle(cnt)
	  center = (int(x),int(y))
	  radius = int(radius)
	  cv2.circle(img, center, radius, (0,255,0),2)
	  print('Calculated using Minimum Enclosing Circle')
	  print('x')
	  print(x)
	  print('y')
	  print(y)


while True:
	ret, img=cam.read()
	#img=cv2.resize(img,(340,220))

	#imgHSV=cv2.cvtColor( img, cv2.COLOR_BGR2HSV )

        imgCrop=img[Y1:Y2, X1:X2]

	trackSquare( lowerBoundG,  upperBoundG  )
        
	cv2.imwrite("imgCenterBot.png", img)
        
        cv2.imshow("cam",imgCrop)
	cv2.waitKey(10)

	if cv2.waitKey(1) == 27:
		break

cam.release()
cv2.destroyAllWindows()
