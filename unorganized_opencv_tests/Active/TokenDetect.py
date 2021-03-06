#!/usr/bin/python

# Creator: Ryan Mathews
# Purpose: Detect color of token by checking picture for all range of colors
# Algorithm will ensure only one color is detected
# Otherwise program will take another snapshot and try again

# Each color tested seperately; others commented out during tests
# However, has the ability to detect all at the same time

import cv2
import numpy as np

# Color Logics

GREEN_P = False
RED_P = False
BLUE_P = False
YELLOW_P = False
PURPLE_P = False

count = 0

# Change to RGB
# Program algorithm to return rgb values of loop of pixels in center of image
# Program range of RGB values surrounding the rgb values of algorithm above
# OpenCV returns color as   G-B-R	(not RGB)

# Green
lowerBoundG=np.array([105,50,25])
upperBoundG=np.array([140,100,75])

# Red
lowerBoundR=np.array([0,50,25])
upperBoundR=np.array([15,100,75])
lowerBoundRe=np.array([350,50,25])
upperBoundRe=np.array([360,100,75])

# Blue
lowerBoundB=np.array([85,30,70])
upperBoundB=np.array([115,60,100])

# Yellow
lowerBoundY=np.array([20,50,25])
upperBoundY=np.array([30,100,75])

# Purple
lowerBoundP=np.array([265,50,25])
upperBoundP=np.array([345,100,75])

# Cyan
lowerBoundC=np.array([160,100,0])
upperBoundC=np.array([185,130,30])

# Grey
# lowerBoundGr=np.array([0,0,40])
# upperBoundGr=np.array([0,0,85])

cam=cv2.VideoCapture(0)
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

	if conts:
		return True

while True:
	ret, img=cam.read()
	img=cv2.resize(img,(340,220))

	# disable camera after capturing img
	#cam.release()

	imgHSV=cv2.cvtColor( img, cv2.COLOR_BGR2HSV )

	# P = PRESENT
	GREEN_P = trackSquare( lowerBoundG,  upperBoundG  )
        RED_P = trackSquare( lowerBoundR,  upperBoundR  )
	#REDE_P = trackSquare( lowerBoundRe, upperBoundRe )
        YELLOW_P = trackSquare( lowerBoundY,  upperBoundY  )
        BLUE_P = trackSquare( lowerBoundB,  upperBoundB  )
	PURPLE_P = trackSquare( lowerBoundP,  upperBoundP  )
	CYAN_P = trackSquare( lowerBoundC, upperBoundC )


	if GREEN_P:
		print("Green")
		count = count + 1
	if RED_P:
		print("Red")
		count = count + 1
	if YELLOW_P:
		print("Yellow")
		count = count + 1
	if BLUE_P:
		print("Blue")
		count = count + 1
	if PURPLE_P:
		print("Purple")
		count = count + 1
	if CYAN_P:
		print("Cyan")
		count = count + 1

	if (count==1):
		print("Detection Successful")
		break
	elif (count<0):
		print("No color detected")
		break
	elif (count>1):
		print("Multiple colors detected")
		break

	# Show Image
	# cv2.imshow("cam",img)

	# Pause Loop
	# cv2.waitKey(10)

	# Escape Key
	# if cv2.waitKey(10) == 27:
	#	break

# Release camera from program otherwise no other program may use it
cam.release()

# Desroy Image/Video Window
# cv2.destroyAllWindows()

