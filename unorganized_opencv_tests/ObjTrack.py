#!/usr/bin/python

# Creator: Ryan Mathews
# Purpose: Detect set colors and draw square around detected mask

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

# COLOR COORDINATES

G_Cx = 0
G_Cy = 0
R_Cx = 0
R_Cy = 0
B_Cx = 0
B_Cy = 0
Y_Cx = 0
Y_Cy = 0
P_Cx = 0
P_Cy = 0
C_Cx = 0
C_Cy = 0

# Green
lowerBoundG=np.array([33,80,40])
upperBoundG=np.array([102,255,255])

# Red
lowerBoundR=np.array([0,100,100])
upperBoundR=np.array([10,255,255])

# Blue
lowerBoundB=np.array([110,50,50])
upperBoundB=np.array([130,255,255])

# Yellow
lowerBoundY=np.array([20,100,100])
upperBoundY=np.array([30,255,255])

#ADDED ------ QE
# Purple
lowerBoundP=np.array([120,50,50])
upperBoundP=np.array([180,255,255])

# Cyan
lowerBoundC=np.array([170,20,0])
upperBoundC=np.array([200,150,200])

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

	if conts:
		return true

		# following lines returns coordinates of square contour trace
                #print(x)
                #print("::")
                #print(y)

def initialColor_START( gr, r, y, b, p, c ):
	if c and r:
		return 1
	if b and y:
		return 2


def initialColor_TURN( gr, r, y, b, p, c ):
	if gr and b:
		return 1
	if p and c: return 2

while True:
	ret, img=cam.read()
	img=cv2.resize(img,(340,220))

	# disable camera after capturing img
	cam.release()

	imgHSV=cv2.cvtColor( img, cv2.COLOR_BGR2HSV )

	# P = PRESENT
	GREEN_P = trackSquare( lowerBoundG,  upperBoundG  )
        RED_P = trackSquare( lowerBoundR,  upperBoundR  )
        YELLOW_P = trackSquare( lowerBoundY,  upperBoundY  )
        BLUE_P = trackSquare( lowerBoundB,  upperBoundB  )
	PURPLE_P = trackSquare( lowerBoundP,  upperBoundP  )
	CYAN_P = trackSquare( lowerBoundC, upperBoundC )


	TURN = initialColor_TURN( GREEN_P, RED_P, YELLOW_P, BLUE_P, PURPLE_P, CYAN_P )
	START = initialColor_START( GREEN_P, RED_P, YELLOW_P, BLUE_P, PURPLE_P, CYAN_P )

	if TURN == 1 or START == 1:

		R_Cx = -3
		R_Cy = 3

		G_Cx = -3
		G_Cy = 0

		B_Cx = -3
		B_Cy = -3

		Y_Cx = 3
		Y_Cy = -3

		P_Cx = 3
		P_Cy = 0

		C_Cx = 3
		C_Cy = 3

	if TURN == 2 or START == 2:

		R_Cx = 3
                R_Cy = -3

                G_Cx = 3
                G_Cy = 0

                B_Cx = 3
                B_Cy = 3

                Y_Cx = -3
                Y_Cy = 3

                P_Cx = -3
                P_Cy = 0

                C_Cx = -3
                C_Cy = -3


	cv2.imshow("cam",img)
#	cv2.waitKey(10)

	if cv2.waitKey(10) == 27:
		break

#cam.release()
cv2.destroyAllWindows()





#  In while loop :
	#trackSquare( lowerBoundBl, upperBoundBl )
        #trackSquare( lowerBoundW,  upperBoundW  )
        #trackSquare( lowerBoundGr, upperBoundGr )


	#cv2.imshow("maskClose",maskClose)
	#cv2.imshow("maskOpen", maskOpen)
	#cv2.imshow("cam", img)
