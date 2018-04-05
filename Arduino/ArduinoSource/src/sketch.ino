#include <Robot.h>
#include <Arduino.h>

#include <Fixed.h>
#include <Direction.h>
#include <Color.h>

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
  int64_t number;
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

Color receiveColor() {
  while(!Serial.available());
  return static_cast<Color>(Serial.read());
}

Fixed receiveFixed() {
  union eight_byte_object x;
  while(Serial.available() < 8);
  Serial.readBytes(x.chars, 8);
  return Fixed(x.number);
}

bool receiveBool() {
  return(receiveIndex() > 0);
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
    case 'c': robot->toggle(Flag::CALIBRATING_LINE); break;
    case 'f': robot->setFlags(Flag::FOLLOWING_LINE); break;
    case 'F': robot->clearFlags(Flag::FOLLOWING_LINE); break;
    
    case ',': robot->setBaseSpeed(receiveFixed()); break; 
    case '<': robot->adjustBaseSpeed(Fixed(-10)); break;
    case '>': robot->adjustBaseSpeed(Fixed(10)); break;
   
    case '/': robot->setCenterOffset(receiveIndex()); break;
    case '"': {
      Fixed f = receiveFixed();
      if(f < Fixed(0)) Serial.write('n');
      else Serial.write('p');
      break;
    }
    case '.': robot->setFollowRange(receiveIndex()); break;
    case 'k': robot->setTravelStop(receiveBool()); break;

    case 'm': robot->move(receiveDirection()); break;
    
    case 'M': {
      Direction dir = receiveDirection();
      Fixed speed = receiveFixed();
      robot->veer(dir, speed);
      break;
    }
    
    case 'n': {
      Direction dir = receiveDirection();
      Fixed dist = receiveFixed();
      robot->nudge(dir, dist);
      break;
    }
    
    case 't': {
      Direction dir = receiveDirection();
      Fixed speed = receiveFixed();
      Fixed dist = receiveFixed();
      robot->travel(dir, speed, dist);
      break;
    }
    
    case 'T': {
      Fixed x = receiveFixed();
      Fixed y = receiveFixed();
      Fixed rot  = receiveFixed();
      Fixed dist = receiveFixed();
      robot->travel(x, y, rot, dist);
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
      robot->veer(dir, speed);
      break;
    }
    
    case 'V': {
      Fixed x = receiveFixed();
      Fixed y = receiveFixed();
      Fixed rot = receiveFixed();
      robot->veer(x, y, rot);
      break;
    }
    
    case 'p': robot->pickUpToken(); break;
    case ' ': robot->stop(); break;
    
    case 'r': {
      Color c = receiveColor();
      robot->storeToken(c);
      break;
    }
    case 'd': robot->dropNextTokenStack(); break;
    case '|': robot->toggle(Flag::CENTERING_CROSS); break;
    case '\\': robot->toggle(Flag::CENTERING_CORNER); break;

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
