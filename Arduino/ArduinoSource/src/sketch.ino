#include <Robot.h>

SortBot robot;

void parseCommand() {
  unsigned char command = Serial.read();
  switch(byte_received) {
    case 'w': robot.move(DIRECTION::FORWARD); break;
    case 'a': robot.move(DIRECTION::LEFT); break;
    case 'x': robot.move(DIRECTION::BACKWARD); break;
    case 'd': robot.move(DIRECTION::RIGHT); break;
    default: for(int i = 0; i < 4; i++) motors[i]->run(RELEASE);
  };
}

void setup() {}

void loop() {
  //for(int i; i < 4; i++) if(edge_sensor[i].edgeDetected()) doSomething(i);
  robot.checkEdges();
  if(Serial.available()) parseCommand();
  robot.approachSpeed();
}
