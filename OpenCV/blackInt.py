#!/usr/bin/python

import cv2
import numpy as np

# Range of HSV values of black for edge detection

# lowBoundB=np.array([0,0,0])
# upBoundB=np.array([360, 100, 80])

# Range of RGB values of Black for edge detection

lowBoundBRGB = np.array([30,30,30])
upBoundBRGB = np.array([100,100,100])

cam=cv2.VideoCapture(1)
kernelOpen=np.ones((5,5))
kernelClose=np.ones((20,20))

Y1=165
Y2=410
X1=195
X2=440

# x coord pixel floor and ceiling values - for line edges
LEFT_EDGE = 100
RIGHT_EDGE = 240

#
Y_MAX = 178
Y_MID_MAX = 155
Y_MIN = 42
Y_MID_MIN = 65

RT = False
RM = False
RB = False

# TRACKSQUARE : returns contour points of detected colors

def trackSquare( lowBound, upBound):
        #mask = cv2.inRange( imgHSV, lowBound, upBound )
        mask = cv2.inRange(img, lowBound, upBound)

        maskOpen=cv2.morphologyEx( mask, cv2.MORPH_OPEN, kernelOpen )
        maskClose=cv2.morphologyEx( maskOpen, cv2.MORPH_CLOSE, kernelClose )

        maskFinal=maskClose
        _,conts,h=cv2.findContours( maskFinal.copy(), cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)

        cv2.drawContours(img,conts,-1,(255,0,0),3)

        if conts:
                return conts
	else:
		print('No contours detected')


while True:
        ret, img=cam.read()
        #img=cv2.resize(img,(340,220))
        img=img[Y1:Y2, X1:X2]

        #imgHSV=cv2.cvtColor( img, cv2.COLOR_BGR2HSV )

        imgGRAY = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
        cv2.inRange(imgGRAY, 10, 255)

        maskOpenGray=cv2.morphologyEx( imgGRAY, cv2.MORPH_OPEN, kernelOpen )
        maskCloseGray=cv2.morphologyEx( maskOpenGray, cv2.MORPH_CLOSE, kernelClose)

        maskFinalGray=maskCloseGray
        _,contsG,hG=cv2.findContours( maskFinalGray.copy(), cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)

        cv2.drawContours(imgGRAY,contsG,-1,(255,0,0),3)

        cnts = trackSquare( lowBoundBRGB,  upBoundBRGB  )

	cv2.imshow("cam", img)
	cv2.imshow("gray", imgGRAY)

	if cv2.waitKey(1) == 27:
		break

cam.release()
cv2.destroyAllWindows()
