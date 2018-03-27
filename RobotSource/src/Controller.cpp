#include "../include/Controller.h"
#include "../include/Robot.h"

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
  } {}

Controller::Controller(SortBot& r, Direction* f_seq, Direction* c_seq, int n) :
  robot(r),
  NUM_LINES(n),
  follow_sequence(f_seq, f_seq + n),
  cover_sequence(c_seq, c_seq + n) {} 

void Controller::coverLine(Direction dir, int num_tokens) const {
  for(int i = 0; i < num_tokens; i++) {
    robot.center();
    if(robot.tokenSeen()) robot.sortToken();
    if(i < num_tokens - 1) robot.followUntilIntersection(dir);
  }
}

void Controller::runAlgorithm() const {
  getchar();
  for(int i = 0; i < 2; i++) robot.moveUntilLine(Direction::FRONT);
  /*for(int i = 0; i < NUM_LINES; i++) {
    robot.followUntilIntersection(follow_sequence[i]);
    coverLine(cover_sequence[i], 4);
  }*/
}
