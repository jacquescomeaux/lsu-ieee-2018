#include <Robot.h>
#include <Arduino.h>
//#include <StandardCplusplus.h>

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
    case 'u': robot->veer(Direction::LEFT); break;
    case 'i': robot->veer(Direction::RIGHT); break;
    case '+': robot->veer(Direction::FRONT); break;
    case '-': robot->veer(Direction::BACK); break;
    /*case 'W': robot->followLine(Direction::FRONT); break;
    case 'A': robot->followLine(Direction::LEFT); break;
    case 'X': robot->followLine(Direction::BACK); break;
    case 'D': robot->followLine(Direction::RIGHT); break;
    case 'Q': robot->followLine(Direction::FRONT_LEFT); break;
    case 'E': robot->followLine(Direction::FRONT_RIGHT); break;
    case 'Z': robot->followLine(Direction::BACK_LEFT); break;
    case 'C': robot->followLine(Direction::BACK_RIGHT); break;
    case 'r': robot->toggleCalibration(); break;
    case 'f': robot->toggleSensorsOutput(); break;
    case 'v': robot->toggleEdgeOutput(); break;
    case '1': robot->adjustKP(-0.01f); break;
    case '2': robot->adjustKP(0.01f); break;
    case '3': robot->adjustKD(-0.01f); break;
    case '4': robot->adjustKD(0.01f); break;
    case '9': robot->adjustDefaultSpeed(-10); break;
    case '0': robot->adjustDefaultSpeed(10); break;
    */case 't': test(); break;
	case 'g': robot->moveSetDistance(Direction::FRONT, moveSetDstAmt);
	case 'b': robot->moveSetDistance(Direction::BACK, moveSetDstAmt);
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
  //robot->checkEdges();
  if(Serial.available()) parseCommand();
//  int time = millis();
  //if(time < 2000) aFunc();
  //else if(time < 4000) bFunc();
 // else {
    //bFunc();
    //veerLeft();
   // robot->stop();
    //test();
  //}
  //robot->approachSpeed();
  robot->update();
  //if(a++%5)
  //robot->correctErrors();
  //delay(10);

}

/*
void aFunc() {
  static bool ran = false;
  if(!ran) robot->move(Direction::BACK);
  ran = true;
}

void bFunc() {
  static bool ran = false;
  //robot->move(Direction::BACK);
  if(!ran) robot->veerLeft();
  ran = true;
  //delay(2000);
  //robot->stop();
  //test();
}*/
