#ifndef SORTINGSYSTEM_H
#define SORTINGSYSTEM_H

#include <Color.h>

#include <Adafruit_MotorShield.h>

#include <MotorShield.h>
#include <MagnetArm.h>
#include <SortingPlate.h>

#include <ArduinoSTL.h>
#include <queue>

class SortingSystem {
  private:
    const int NUM_COLORS;
    const int COLOR_POSITIONS[8];
    std::queue<int> task_buffer;
    int state;
    MotorShield sorting_shields[2];
    MagnetArm token_arm;
    SortingPlate storage_plate;
  public:
    SortingSystem();
    void pickUpToken();
    void storeToken(Color);
    void dropNextTokenStack();
    void continueSorting();
};

#endif//SORTINGSYSTEM_H
