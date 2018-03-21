#include <Robot.h>
#include <Arduino.h>

#include <Fixed.h>

#define moveSetDstAmt 4 //how far the robot moves via moveSetDistance (in inches)

SortBot* robot;

void setPins() { //allows pins 18-21 to be used with the Encoders. **If the robot stops functioning comment this out.**
  pinMode(18, INPUT);
  pinMode(19, INPUT);
  pinMode(20, INPUT);
  pinMode(21, INPUT);
}

void test() {
  Serial.println("still alive");
  while(true);
}

void recievePIDCommand(unsigned int var) {
  while(Serial.available() < 2);
  unsigned char param1 = Serial.read();
  unsigned char param2 = Serial.read();
  unsigned int term;
  Fixed adjustment;
  if(param1 == '1') term = 0;
  else if(param1 == '2') term = 1;
  else if(param1 == '3') term = 2;
  else return;
  if(param2 == '9') adjustment = Fixed(-0.001);
  else if(param2 == '0') adjustment = Fixed(0.001);
  else return;
  robot->adjustPID(var, term, adjustment); 
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
    case 'u': robot->steer(Direction::COUNTER_CLOCKWISE); break;
    case 'i': robot->steer(Direction::CLOCKWISE); break;
    case 'y': robot->steer(Direction::LEFT); break;
    case 'o': robot->steer(Direction::RIGHT); break;
    case 'r': robot->toggle(Flag::CALIBRATING_LINE); break;
    case 'f': robot->toggle(Flag::FOLLOWING_LINE); break;
    case 'v': robot->toggle(Flag::PRINTING_LINE); break;
    case 'h': robot->toggle(Flag::STOPPING_INT); break;
    case '1': Serial.println("Adjusting x"); receivePIDCommand(0); break;
    case '2': Serial.println("Adjusting r"); receivePIDCommand(1); break;
    case '3': Serial.println("Adjusting rot"); receivePIDCommand(2); break;
    case '<': robot->adjustBaseSpeed(Fixed(-10)); break;
    case '>': robot->adjustBaseSpeed(Fixed(10)); break;
    case 't': test(); break;
    case 'g': robot->travel(Direction::FRONT, Fixed(11), Fixed(40)); break;
    case 'b': robot->travel(Direction::COUNTER_CLOCKWISE, Fixed(10)); break;
    //case 'p': robot->pickUpToken(); break;
    case '|': robot->center(0); break;
    case '\\': robot->toggle(Flag::CENTERING_INT); break;
    default: robot->stop();
  }
}

void setup() {
  setPins();
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
