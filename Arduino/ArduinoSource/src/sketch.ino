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

Fixed receiveFixed() {
  union eight_byte_object x;
  unsigned long start = millis();
  while(Serial.available() < 8) if((millis() - start) > 20000) Serial.write(Serial.read());
  Serial.readBytes(x.chars, 8);
  return Fixed(x.number);
}

VelocityVector receiveVelocityVector() {
  Fixed x = receiveFixed();
  Fixed y = receiveFixed();
  Fixed rot = receiveFixed();
  VelocityVector v(x, y, rot);
  return v;
}

Color receiveColor() {
  while(!Serial.available());
  return static_cast<Color>(Serial.read());
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
    case 'c': robot->toggleFlags(Flag::CALIBRATING_LINE); Serial.write('c'); break;
    case 'f': robot->setFlags(Flag::FOLLOWING_LINE); Serial.write('f'); break;
   
    //picocom testing case — changing this will not break stuff — use it for whatever is needed
    case '"': {
      robot->move(VelocityVector(0, 70, 0));
      //robot->setTravelStop(true);
      //robot->travel(VelocityVector(-120, 0, 0), 5);
      break;
    }
    case '/': robot->setFollowOffset(receiveIndex()); break;
    case '.': robot->setFollowRange(receiveIndex()); break;
    case 'k': robot->setTravelStop(receiveBool()); break;
    case 'm': robot->move(receiveVelocityVector()); break;
    case 'n': {
      VelocityVector v = receiveVelocityVector();
      Fixed dist = receiveFixed();
      robot->nudge(v, dist);
      break;
    }
    case 't': {
      Serial.write('0');
      VelocityVector v = receiveVelocityVector();
      Serial.write('1');
      Fixed dist = receiveFixed();
      Serial.write('2');
      robot->travel(v, dist);
      Serial.write('3');
      break;
    }
    case 's': {
      VelocityVector dv = receiveVelocityVector();
      robot->steer(dv);
      break;
    }
    case 'v': {
      VelocityVector dv = receiveVelocityVector();
      robot->veer(dv);
      break;
    }
    case ' ': robot->stop(); break;
    case 'p': robot->pickUpToken(); break;
    case 'r': {
      Color c = receiveColor();
      robot->storeToken(c);
      break;
    }

    case 'd': robot->dropNextTokenStack(); Serial.write('d'); break;
    
    default: robot->stop();
  }
}

void setup() {
  Serial.begin(115200);
  robot = new SortBot();
  TWBR = ((F_CPU /400000l) - 16) / 2; //change i2c clock to 400KHz
  robot->stop();
  while(!robot->ready());
  delay(500);
}

void loop() {
  if(Serial.available()) parseCommand();
  robot->update();
}
