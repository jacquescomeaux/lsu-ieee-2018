#include <Robot.h>
#include <Arduino.h>

#include <Fixed.h>
#include <Direction.h>

#define moveSetDstAmt 4 //how far the robot moves via moveSetDistance (in inches)

SortBot* robot;

union two_byte_object {
  unsigned char bytes[2];
  char chars[2];
  unsigned int number;
};

union eight_byte_object {
  unsigned char bytes[8];
  char chars[8];
  Fixed number;
};

unsigned int receiveIndex() {
  union two_byte_object i;
  while(Serial.available() < 2);
  Serial.readBytes(i.chars, 2);
  return i.number;
}

Direction receiveDirection() {
  while(!Serial.available());
  return static_cast<Direction>(Serial.read());
}

Fixed receiveFixed() {
  union eight_byte_object x;
  while(Serial.available() < 8);
  Serial.readBytes(x.chars, 8);
  return x.number;
}

void receivePIDCommand(unsigned int var) {
  while(Serial.available() < 2);
  unsigned char param1 = Serial.read();
  unsigned char param2 = Serial.read();
  unsigned int term;
  Fixed adjustment;
  if(param1 == '1') {term = 0; Serial.println("P");}
  else if(param1 == '2') {term = 1; Serial.println("I");}
  else if(param1 == '3') {term = 2; Serial.println("D");}
  else return;
  if(param2 == '9') adjustment = Fixed(-0.001);
  else if(param2 == '0') adjustment = Fixed(0.001);
  else if(param2 == '8') adjustment = Fixed(-0.01);
  else if(param2 == '-') adjustment = Fixed(0.01);
  else if(param2 == '(') adjustment = Fixed(-0.1);
  else if(param2 == ')') adjustment = Fixed(0.1);
  else if(param2 == '[') adjustment = Fixed(-0.0001); //tiny adjustments for i term
  else if(param2 == ']') adjustment = Fixed(0.0001);
  else if(param2 == '{') adjustment = Fixed(-1);
  else if(param2 == '}') adjustment = Fixed(1);
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
    
    case '1': Serial.print("Adjusting x"); receivePIDCommand(0); break;
    case '2': Serial.print("Adjusting y"); receivePIDCommand(1); break;
    case '3': Serial.print("Adjusting rot"); receivePIDCommand(2); break;
    
    case ',': robot->setBaseSpeed(receiveFixed()); break; 
    case '<': robot->adjustBaseSpeed(Fixed(-10)); break;
    case '>': robot->adjustBaseSpeed(Fixed(10)); break;
   
    case '/': robot->setCenterOffset(recieveIndex()) break;
    case '.': robot->setFollowRange(recieveIndex()) break;

    case 'm': robot->move(recieveDirection()); break;
    
    case 't': {
      Direction dir = receiveDirection();
      Fixed speed = receiveFixed();
      Fixed dist = receiveFixed();
      robot->travel(dir, speed, dist);
      break;
    }
    
    case 's': {
      Direction dir = receiveDirection();
      Fixed amount = receiveFixed();
      robot->steer(dir, amount);
      break;
    }
    
    case 'v': {
      Direction dir = receiveDirection();
      Fixed speed = receiveFixed();
      Fixed dist = receiveFixed();
      robot->veer(recieveDirection(), speed, dist); break;
    }
    
    case 'V': {
      Fixed x = receiveFixed();
      Fixed y = receiveFixed();
      Fixed rot = receiveFixed();
      robot->veer(x, y, rot);
      break;
    }
    
    case 'p': robot->pickUpToken(); break;
    case 'm': robot->storeToken(Color::RED); break;
    case 'l': robot->dropNextTokenStack(); break;
    case '|': robot->toggle(Flag::CENTERING_CROSS); break;
    case '\\': robot->toggle(Flag::CENTERING_CORNER); break;
    //case '?' : Serial.write(robot->atIntersection() ? 'y' : 'n'); break;
    default: robot->stop();
  }
}

void setup() {
  Serial.begin(9600);
  robot = new SortBot();
  TWBR = ((F_CPU /400000l) - 16) / 2; //change i2c clock to 400KHz
  robot->stop();
  while(!robot->ready());
  //Serial.println("Robot ready");
  delay(500);
}

void loop() {
  if(Serial.available()) parseCommand();
  robot->update();
}
