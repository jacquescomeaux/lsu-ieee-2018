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
  offset_sequence {16, 0, 8, 0, 0, 24}, 
  dist_sequence {8.48, 6, 8.48, 8.48, 6, 8.48},
  travel_sequence {16, 3, 16, 12, 16, 3} {}

Controller::Controller(SortBot& r, Direction* f_seq, Direction* c_seq, int n) :
  robot(r),
  NUM_LINES(n),
  follow_sequence(f_seq, f_seq + n),
  cover_sequence(c_seq, c_seq + n) {} 

void Controller::coverLine(Direction dir, bool cross, int offset, int num_tokens) const {
  for(int i = 0; i < num_tokens; i++) {
    robot.center(cross, offset);
    if(robot.tokenSeen());//robot.sortToken();
    robot.snapToLine(dir, 2);
    if(i == num_tokens - 1) break;
    robot.followLine(dir);
    robot.travel(dir, 40, dist_sequence[i], true);
  }
}

void Controller::waitForEnter() const {
  getchar();
}

void Controller::runAlgorithm() const {
  std::cout << "Waiting for enter key" << std::endl; 
  waitForEnter();
  #if 0
  robot.travel(Direction::FRONT, 120, 2, true);
  //robot.move(Direction::FRONT);
  //robot.center(16, false);
  #else 
  robot.setSpeed(30);
  robot.toggleCalibration();
  robot.travel(Direction::FRONT, 30, 12, true);
  robot.snapToLine(Direction::LEFT, 6);
  robot.travel(Direction::COUNTER_CLOCKWISE, 70, 54, true);
  robot.toggleCalibration();
  
  robot.setSpeed(120);
  robot.snapToLine(Direction::LEFT, 6);
  
  robot.setSpeed(60);
  
  for(int i = 0; i < NUM_LINES; i++) {
    robot.followLine(follow_sequence[i]);
    robot.travel(follow_sequence[i], 120, travel_sequence[i], false);
    robot.followUntilIntersection(follow_sequence[i]);
    coverLine(cover_sequence[i], type_sequence[i], offset_sequence[i], 4);
  }

  robot.followUntilIntersection(Direction::BACK_RIGHT);
  robot.travel(Direction::BACK_RIGHT, 60, 3, true);
  robot.dropTokenStack(Color::RED);
  robot.travel(Direction::FRONT_LEFT, 60, 3, true);

  robot.followUntilIntersection(Direction::FRONT);

  robot.followUntilIntersection(Direction::RIGHT);
  robot.travel(Direction::RIGHT, 60, 3, true);
  robot.dropTokenStack(Color::RED);
  robot.travel(Direction::LEFT, 60, 3, true);
  
  robot.followUntilIntersection(Direction::FRONT);

  robot.followUntilIntersection(Direction::FRONT_RIGHT);
  robot.travel(Direction::FRONT_RIGHT, 60, 3, true);
  robot.dropTokenStack(Color::RED);
  robot.travel(Direction::BACK_LEFT, 60, 3, true);

  robot.followUntilIntersection(Direction::LEFT);

  robot.followUntilIntersection(Direction::FRONT_LEFT);
  robot.travel(Direction::FRONT_LEFT, 60, 3, true);
  robot.dropTokenStack(Color::RED);
  robot.travel(Direction::BACK_RIGHT, 60, 3, true);
  
  robot.followUntilIntersection(Direction::BACK);

  robot.followUntilIntersection(Direction::LEFT);
  robot.travel(Direction::LEFT, 60, 3, true);
  robot.dropTokenStack(Color::RED);
  robot.travel(Direction::RIGHT, 60, 3, true);

  robot.followUntilIntersection(Direction::BACK);

  robot.followUntilIntersection(Direction::BACK_LEFT);
  robot.travel(Direction::BACK_LEFT, 60, 3, true);
  robot.dropTokenStack(Color::RED);
  robot.travel(Direction::FRONT_RIGHT, 60, 3, true);
  
  for(int i = 0; i < 4; i++) robot.followUntilIntersection(Direction::FRONT_RIGHT);
  robot.travel(Direction::FRONT_RIGHT, 60, 3, true);
  robot.dropTokenStack(Color::RED);
  #endif
}
