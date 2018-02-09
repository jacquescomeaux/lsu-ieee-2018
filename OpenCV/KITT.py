#!/usr/bin/env python

from __future__ import print_function
import sys
import cv2
import numpy as np
import argparse
import cv2

boundaries = [
	([17, 15, 100], [50, 56, 200]),
	([86, 31, 4], [200, 88, 50]),
	([25, 146, 190], [62, 174, 250])
	([103, 86, 65], [145, 133, 128])

def main(argv):
	cap = cv2.VideoCapture(2)
