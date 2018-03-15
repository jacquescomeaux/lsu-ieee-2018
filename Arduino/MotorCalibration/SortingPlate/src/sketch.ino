#include <Adafruit_MotorShield.h>
#include <SortingPlate.h>

SortingPlate* test_plate;

void setup() {
  Adafruit_MotorShield AFMS(0x61);
  AFMS.begin();
  test_plate = new SortingPlate(AFMS.getStepper(200, 1));
}

void loop() {
  
}
