#include <Robot.h>

SortBot robot;

void parseCommand() {
  unsigned char command = Serial.read();
  switch(command) {
    case 'w': robot.move(DIRECTION::FRONT); break;
    case 'a': robot.move(DIRECTION::LEFT); break;
    case 'x': robot.move(DIRECTION::BACK); break;
    case 'd': robot.move(DIRECTION::RIGHT); break;
    default: robot.stop();//for(int i = 0; i < 4; i++) motors[i]->run(RELEASE);
  }
}

void setup() {}

void loop() {
  //for(int i; i < 4; i++) if(edge_sensor[i].edgeDetected()) doSomething(i);
  robot.checkEdges();
  if(Serial.available()) parseCommand();
  robot.approachSpeed();
}
