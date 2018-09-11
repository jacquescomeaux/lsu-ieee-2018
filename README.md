# lsu-ieee-2018
Raspberry Pi and Arduino source code for LSU's 2018 IEEE R5 autonomous robot

This repository contains the code written for Louisiana State University's IEEE Region 5 Student Robotics Competition entry.

The competition's task was to build a small autonomous robot which was capable of detecting colored coins on a 8' by 8' platform and delivering them to the correct location

The robot contained two microcontrollers, connected via USB:
  - an Arduino Mega 2560 for interfacing with sensors and motors
  - a Raspberry Pi 3b+ for maintaining robot state information, processing camera data, and sending commands to arduino

The code was written in C++ 11 in an object-oriented style and took advantage of open-source libraries including OpenCV

The code in Arduino/ArduinoSource handled low-level robot tasks such as moving, line-following, and stopping upon detection of hazards. This code was optimized to compensate for the arduino's limited hardware capabilites. Most notably, the arduino has only a single-core processor and lacks an FPU; beacuse of this a software process scheduler was written for handling multiple tasks in real-time, and a fixed point data type was created for doing floating-point–like operations with integer speed. Also included in the arduino code was a PID controller and a novel algorithm for quickly processing data from the robot's 32 reflectance sensors.

The code in RobotSource was run on the raspberry pi and used information from the robot's cameras to make decisions about the robot's next action. It was written in a modular manner such that the same code could be adapted to be used for other robots or for competitions with different rules, in many cases by only changing the main.cpp file.
