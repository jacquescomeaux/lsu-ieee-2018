#ifndef SORTINGSYSTEM_H
#define SORTINGSYSTEM_H

#include <Color.h>

#include <Adafruit_MotorShield.h>
#include <MagnetArm.h>
#include <LED.h>
//#include <RGBSensor.h>
#include <SortingPlate.h>

#include <ArduinoSTL.h>
#include <queue>

class SortingSystem {
  private:
    const int NUM_COLORS;
    const int COLOR_POSITIONS[8];
    std::queue<int> task_buffer;
    int state;
    MagnetArm token_arm;
    LED token_light;
    //RGBSensor color_sensor;
    SortingPlate storage_plate;
  protected:
    SortingSystem();
    SortingSystem(Adafruit_StepperMotor*, Adafruit_StepperMotor*);
  public:
    void pickUpToken();
    //Color checkTokenColor() const;
    void storeToken(Color);
    void dropNextTokenStack();
    void continueSorting();
};

#endif//SORTINGSYSTEM_H
