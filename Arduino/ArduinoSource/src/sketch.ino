#include <Robot.h>
#include <Arduino.h>

#include <Fixed.h>

#include <VelocityVector.h>

#include <Color.h>

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

VelocityVector receiveVelocityVector() {
  Fixed x = recieveFixed();
  Fixed y = recieveFixed();
  Fixed rot = receiveFixed();
  VelocityVector v(x, y, rot);
  return v;
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
    case 'c': robot->toggleFlags(Flag::CALIBRATING_LINE); break;
    case 'f': robot->setFlags(Flag::FOLLOWING_LINE); break;
    //case 'F': robot->clearFlags(Flag::FOLLOWING_LINE); break;
    
    /*
    CASE FOR PICOCOM TESTING
    case '"': {
      robot->setTravelStop(true);
      robot->travel(VelocityVector(-120, 0, 0), 5);
      break;
    }*/
    case '/': robot->setCenterOffset(receiveIndex()); break;
    case '.': robot->setFollowRange(receiveIndex()); break;
    case 'k': robot->setTravelStop(receiveBool()); break;
    case ',': robot->setBaseSpeed(receiveFixed()); break; 
    //case '<': robot->adjustBaseSpeed(Fixed(-10)); break;
    //case '>': robot->adjustBaseSpeed(Fixed(10)); break;

    case 'm': robot->move(receiveVelocityVector()); break;
    
    case 'n': {
      VelocityVector v = receiveVelocityVector();
      Fixed dist = receiveFixed();
      robot->nudge(v, dist);
      break;
    }
    
    case 't': {
      VelocityVector v = receiveVelocityVector();
      Fixed dist = receiveFixed();
      robot->travel(v, dist);
      break;
    }
    
    case 's': {
      VelocityVector dv = receiveVelocityVector();
      Fixed amount = receiveFixed();
      robot->steer(dv, amount);
      break;
    }
    
    case 'v': {
      VelocityVector dv = receiveVelocityVector();
      Fixed speed = receiveFixed();
      robot->veer(dv, speed);
      break;
    }
    
    case ' ': robot->stop(); break;

    case 'p': robot->pickUpToken(); break;
    
    case 'r': {
      Color c = receiveColor();
      robot->storeToken(c);
      break;
    }

    case 'd': robot->dropNextTokenStack(); break;
    
    case '|': robot->toggleFlags(Flag::CENTERING); break;
    //case '|': robot->toggle(Flag::CENTERING_CROSS); break;
    //case '\\': robot->toggle(Flag::CENTERING_CORNER); break;

    default: robot->stop();
  }
}

void setup() {
  Serial.begin(115200);
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
