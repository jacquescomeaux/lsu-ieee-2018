#include <Robot.h>
#include <Arduino.h>

#include <Fixed.h>

#define moveSetDstAmt 4 //how far the robot moves via moveSetDistance (in inches)

SortBot* robot;

void test() {
  Serial.println("still alive");
  while(true);
}

void parseCommand() {
  unsigned char command = Serial.read();
  switch(command) {
    case 'w': robot->move(Direction::FRONT); break;
    case 'a': robot->move(Direction::LEFT); break;
    case 'x': robot->move(Direction::BACK); break;
    case 'd': robot->move(Direction::RIGHT); break;
    case 'q': robot->move(Direction::FRONT_LEFT); break;
    case 'e': robot->move(Direction::FRONT_RIGHT); break;
    case 'z': robot->move(Direction::BACK_LEFT); break;
    case 'c': robot->move(Direction::BACK_RIGHT); break;
    case 'k': robot->move(Direction::CLOCKWISE); break;
    case 'j': robot->move(Direction::COUNTER_CLOCKWISE); break;
    case 'r': robot->toggle(Flag::CALIBRATING_LINE); break;
    case 'f': robot->toggle(Flag::FOLLOWING_LINE); break;
    case '1': robot->adjustXP(Fixed(-0.01)); break;
    case '2': robot->adjustXP(Fixed(0.01)); break;
    case '3': robot->adjustYP(Fixed(-0.01)); break;
    case '4': robot->adjustYP(Fixed(0.01)); break;
    case '5': robot->adjustRotP(Fixed(-0.01)); break;
    case '6': robot->adjustRotP(Fixed(0.01)); break;
    case '9': robot->adjustBaseSpeed(Fixed(-10)); break;
    case '0': robot->adjustBaseSpeed(Fixed(10)); break;
    case 't': test(); break;
    case 'g': robot->travel(Direction::FRONT, Fixed(moveSetDstAmt)); break;
    case 'b': robot->travel(Direction::BACK, Fixed(moveSetDstAmt)); break;
    case 'p': robot->pickUpToken(); break;
    default: robot->stop();
  }
}

void setup() {
  robot = new SortBot();
  robot->stop();
  Serial.begin(9600);
  Serial.println("Robot ready");
  delay(500);
}

void loop() {
  if(Serial.available()) parseCommand();
  robot->update();
}
