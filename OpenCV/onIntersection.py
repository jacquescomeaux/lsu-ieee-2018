#!/usr/bin/python

import cv2
import numpy as np

# Range of HSV values of black for edge detection

# lowBoundB=np.array([0,0,0])
# upBoundB=np.array([360, 100, 80])

# Range of RGB values of Black for edge detection

lowBoundBRGB = np.array([0,0,0])
upBoundBRGB = np.array([40,40,40])

cam=cv2.VideoCapture(1)
kernelOpen=np.ones((5,5))
kernelClose=np.ones((20,20))

# x coord pixel floor and ceiling values - for line edges
LEFT_EDGE = 100
RIGHT_EDGE = 240

#
Y_MAX = 178
Y_MID_MAX = 155
Y_MIN = 42
Y_MID_MIN = 65

#
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
        _,conts,h=cv2.findContours( maskFinal.copy(), cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE )

	cv2.drawContours(img,conts,-1,(255,0,0),3)

        if conts:
                return conts
        else:
                print('No contours detected')

def whatInter( conts ):

	RT = False
	RM = False
	RB = False

	# DEBUGGING SESSION -> QE

	c = conts[0]

	# conts with x > 215
	c250x = c[c[:,:,0] > 215, :]

	# conts with x < 125
	c120x = c[c[:,:,0] < 125, :]

	print('conts > 215')
	print(c250x)

	print('conts < 125')
	print(c120x)

	# find min and max y values of contours with x > 250
	# used to find upper and lower right corner values
	# c250maxY = tuple(c250x[c250x[:,:,1].argmax()][0])[:,1]
	c250maxY = c250x[c250x[:,1].argmax()][1]
	c250minY = c250x[c250x[:,1].argmin()][1]

	# find min and max y values of contours with x < 120
	# used to find upper and lower left corner values
	c120maxY = c120x[c120x[:,1].argmax()][1]
	c120minY = c120x[c120x[:,1].argmin()][1]

	if (c250maxY-c250minY) < 75:
		RM = True

	elif c250maxY > Y_MAX:
		RB = True
		if c250minY < Y_MID_MAX:
			RM = True

	elif c250minY < Y_MIN:
		RT = True
		if c250maxY > Y_MID_MIN:
			RM = True

	print('c250minY')
	print(c250minY)
	print('c250maxY')
	print(c250maxY)

	print('RT')
	print(RT)
	print('YMAX')
	print(Y_MAX)


	if RM:
		if RT:
			print('Shape 5')
		elif RB:
			print('Shape 4')
		else:
			print('Shape 1')
	else:
		if RT:
			print('Shape 3')
		elif RB:
			print('Shape 2')
		else:
			print('Not on intersection')


while True:
        ret, img=cam.read()
        img=cv2.resize(img,(340,220))

        #imgHSV=cv2.cvtColor( img, cv2.COLOR_BGR2HSV )

	imgGRAY = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
	cv2.inRange(imgGRAY, 10, 255)

	maskOpenGray=cv2.morphologyEx( imgGRAY, cv2.MORPH_OPEN, kernelOpen )
        maskCloseGray=cv2.morphologyEx( maskOpenGray, cv2.MORPH_CLOSE, kernelClose )

        maskFinalGray=maskCloseGray
        _,contsG,hG=cv2.findContours( maskFinalGray.copy(), cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE )

        cv2.drawContours(imgGRAY,contsG,-1,(255,0,0),3)
	cv2.imwrite("GRAYCalib.png", imgGRAY)

        cnts = trackSquare( lowBoundBRGB,  upBoundBRGB  )

	cv2.imwrite("Calibration.png", img)

        onLine = whatInter( cnts )

        if onLine:
                print('Centered')
        else: print('Adjust')

	# export picture w/ contours to png file
	# cv2.imwrite("Calibration.png", img)

	cv2.waitKey()

        # cv2.imshow("cam",img)

        # BREAK ON ESCAPE KEY
	# if cv2.waitKey(10) == 27:
	#        break

cam.release();
cv2.destroyAllWindows;

