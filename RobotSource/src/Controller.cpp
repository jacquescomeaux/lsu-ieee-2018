#include "../include/Controller.h"
#include "../include/Robot.h"

#include <iostream>

Controller::Controller(SortBot& r) :
  robot(r),
  NUM_LINES(6),
  follow_sequence {
    Direction::LEFT,
    Direction::FRONT,
    Direction::FRONT,
    Direction::RIGHT,
    Direction::BACK,
    Direction::BACK
  },
  cover_sequence {
    Direction::FRONT_RIGHT,
    Direction::LEFT,
    Direction::BACK_RIGHT,
    Direction::FRONT_RIGHT,
    Direction::LEFT,
    Direction::BACK_RIGHT
  },
  type_sequence {false, true, false, false, true, false},
  offset_sequence {16, 0, 8, 0, 0, 24} {}

Controller::Controller(SortBot& r, Direction* f_seq, Direction* c_seq, int n) :
  robot(r),
  NUM_LINES(n),
  follow_sequence(f_seq, f_seq + n),
  cover_sequence(c_seq, c_seq + n) {} 

void Controller::coverLine(Direction dir, bool cross, int offset, int num_tokens) const {
  for(int i = 0; i < num_tokens; i++) {
    robot.center(cross, offset);
    //if(robot.tokenSeen())
    //robot.sortToken();
    if(i == num_tokens - 1) break;
    robot.snapToLine(dir, 2);
    robot.followLine(dir);
    robot.travel(dir, 60, 1, false);
    robot.followUntilIntersection(dir);
  }
}

void Controller::runAlgorithm() const {
  std::cout << "Waiting for enter key" << std::endl; 
  getchar();

  robot.toggleCalibration();
  robot.moveUntilLine(Direction::FRONT, 30);
  robot.travel(Direction::FRONT, 30, 3, false);
  robot.moveUntilLine(Direction::FRONT, 30);
  robot.travel(Direction::CLOCKWISE, 70, 52, true); //prev dist 52
  robot.toggleCalibration();
  robot.setSpeed(60);
  robot.snapToLine(Direction::LEFT, 6);
  for(int i = 0; i < NUM_LINES; i++) {
    robot.travel(follow_sequence[i], 60, 1, false);
    robot.followUntilIntersection(follow_sequence[i]);
    coverLine(cover_sequence[i], type_sequence[i], offset_sequence[i], 4);
  }
}
