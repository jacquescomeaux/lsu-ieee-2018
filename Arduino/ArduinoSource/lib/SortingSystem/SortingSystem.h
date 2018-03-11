#ifndef SORTINGSYSTEM_H
#define SORTINGSYSTEM_H

#include <Color.h>

#include <MagnetArm.h>
#include <LED.h>
//#include <RGBSensor.h>
//#include <SortingPlate.h>

#include <ArduinoSTL>
#include <queue>

class SortingSystem {
  private:
    const int NUM_COLORS;
    const int COLOR_POSITIONS[NUM_COLORS];
    std::queue<Color> task_buffer;
    int state;
    const MagnetArm token_arm;
    LED token_light;
    //RGBSensor color_sensor;
    SortingPlate storage_plate, selector_plate;
  protected:
    SortingSystem();
  public:
    void pickUpToken();
    //Color checkTokenColor() const;
    void storeToken(Color);
    void dropNextTokenStack();
    void continueSorting();
};

#endif//SORTINGSYSTEM_H
