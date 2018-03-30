#!/usr/bin/python

import cv2
import numpy as np

# Constants

cam = cv2.VideoCapture(0)

X1=260
X2=300
Y1=200
Y2=400


B=0
G=0
R=0
sum=0

while True:

        ret, img = cam.read()

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

if (avR > 200):
        if (avG > 200):
                print('YELLOW')
        if (avG < 100) and (avB < 100):
                print('RED')

elif (avR < 100):
        if (avB < 80):
                print('GREEN')
        if (avG < 80):
                print('BLUE')
        if (avG > 180) and (avB > 180):
                print('CYAN')

elif (avG < 80) and (avR > 80):
        print('PURPLE')

elif (avG > 80) and (avR > 80) and (avB > 80):
        print('GREY')

else:
        print('No color found')



print('R')
print(avR)
print('G')
print(avG)
print('B')
print(avB)

cv2.imwrite("ColorCalib.png", img)

cam.release()

