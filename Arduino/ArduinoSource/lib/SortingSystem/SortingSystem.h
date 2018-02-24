#ifndef SORTINGSYSTEM_H
#define SORTINGSYSTEM_H

//#include <Color.h>

#include <MagnetArm.h>
#include <LED.h>
//#include <RGBSensor.h>
//#include <SortingPlate.h>

class SortingSystem {
  private:
    const MagnetArm token_arm;
    LED token_light;
    //RGBSensor color_sensor;
    //SortingPlate storage_plate, selector_plate;
  protected:
    SortingSystem();
  public:
    void pickUpToken() const;
  //  Color checkTokenColor() const;
    void sortToken() const;
    //void dropTokenStack(Color) const;
};

#endif//SORTINGSYSTEM_H
