# lsu-ieee-2018
Raspberry Pi and Arduino source code for LSU's 2018 IEEE R5 autonomous robot

This repository contains the code written for Louisiana State University's IEEE Region 5 Student Robotics Competition entry.

The competition's task was to build a small autonomous robot which was capable of detecting colored coins on a 8' by 8' platform and delivering them to the correct location

The robot contained two microcontrollers, connected via USB:
  - an Arduino Mega 2560 for interfacing with sensors and motors
  - a Raspberry Pi 3b+ for maintaining robot state information, processing camera data, and sending commands to arduino

The code was written in C++ 11 in an object-oriented style and took advantage of open-source libraries including OpenCV
