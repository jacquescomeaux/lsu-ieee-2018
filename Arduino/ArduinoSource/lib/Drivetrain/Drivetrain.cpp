#include <Drivetrain.h>

Drivetrain::Drivetrain() :
  AFMS {
    Adafruit_MotorShield(0x61),
    Adafruit_MotorShield(0x62),
  },
  wheels {
    Wheel(AFMS[0].getMotor(1)),
    Wheel(AFMS[0].getMotor(2)),
    Wheel(AFMS[1].getMotor(1)),
    Wheel(AFMS[1].getMotor(2)),
  } {}

void Drivetrain::move(DIRECTION dir) {

}

void Drivetrain::stop() {
  for(auto w : wheels) w.stop();
}
