#!/usr/bin/python

import cv2
import numpy as np

# Constants

cam = cv2.VideoCapture(0)

X1=220
X2=260
Y1=360
Y2=520

B=0
G=0
R=0
sum=0

while True:

        ret, img = cam.read()

	img=cv2.cvtColor(img, cv2.COLOR_BGR2HSV)

        if img.any():

                for i in range(X1,X2):
                        for j in range(Y1,Y2):
                                B = B + img[i][j][0]
                                G = G + img[i][j][1]
                                R = R + img[i][j][2]
                                sum = sum + 1
                break


avB=B/sum
avG=G/sum
avR=R/sum

#120,121
if (avB > 95) and (avB < 125):
	if (avG > 90):
		print('BLUE')
	else:
		print('GREY')

#154
if (avB > 140) and (avB < 170):
	print('RED')

if (avB > 60) and (avB < 90):
	if (avR > 90):
		print('CYAN')
	else:
		print('YELLOW')




print('B')
print(avB)
print('G')
print(avG)
print('R')
print(avR)

cv2.imwrite("ColorCalib.png", img)

cam.release()

