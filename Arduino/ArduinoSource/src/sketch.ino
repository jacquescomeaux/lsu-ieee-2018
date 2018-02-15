#include <Robot.h>

SortBot robot;

void parseCommand() {
  unsigned char command = Serial.read();
  switch(command) {
    case 'w': robot.move(Direction::FRONT); break;
    case 'a': robot.move(Direction::LEFT); break;
    case 'x': robot.move(Direction::BACK); break;
    case 'd': robot.move(Direction::RIGHT); break;
    case 'q': robot.move(Direction::FRONT_LEFT); break;
    case 'e': robot.move(Direction::FRONT_RIGHT); break;
    case 'z': robot.move(Direction::BACK_LEFT); break;
    case 'c': robot.move(Direction::BACK_RIGHT); break;
    case 'W': robot.followLine(Direction::FRONT); break;
    case 'A': robot.followLine(Direction::LEFT); break;
    case 'X': robot.followLine(Direction::BACK); break;
    case 'D': robot.followLine(Direction::RIGHT); break;
    case 'Q': robot.followLine(Direction::FRONT_LEFT); break;
    case 'E': robot.followLine(Direction::FRONT_RIGHT); break;
    case 'Z': robot.followLine(Direction::BACK_LEFT); break;
    case 'C': robot.followLine(Direction::BACK_RIGHT); break;
    default: robot.stop();
  }
}

void setup() {}

void loop() {
  robot.checkEdges();
  if(Serial.available()) parseCommand();
  robot.approachSpeed();
}
