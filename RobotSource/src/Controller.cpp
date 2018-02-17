#include "../include/Controller.h"
#include "../include/Robot.h"

Controller::Controller(Robot& r) : robot(r), NUM_LINES(6) {
  follow_sequence[0] =  Direction::LEFT;
  follow_sequence[1] =  Direction::FRONT;
  follow_sequence[2] =  Direction::FRONT;
  follow_sequence[3] =  Direction::RIGHT;
  follow_sequence[4] =  Direction::BACK;
  follow_sequence[5] =  Direction::BACK;

  cover_sequence[0] =  Direction::FRONT_RIGHT;
  cover_sequence[1] =  Direction::LEFT;
  cover_sequence[2] =  Direction::BACK_RIGHT;
  cover_sequence[3] =  Direction::FRONT_RIGHT;
  cover_sequence[4] =  Direction::LEFT;
  cover_sequence[5] =  Direction::BACK_RIGHT;
}

Controller::Controller(Robot& r, Direction* f_seq, Direction* c_seq, int n) : robot(r), NUM_LINES(n) {
  for(int i = 0; i < n; i++) {
    follow_sequence[i] = f_seq[i];
    cover_sequence[i] = c_seq[i];
  }
}

void Controller::coverLine(Direction dir, int num_tokens) const {
  for(int i = 0; i < num_tokens; i++) {
    robot.center();
    if(robot.tokenSeen()) robot.sortToken();
    robot.followUntilIntersection(dir);
  }
}

void Controller::runAlgorithm() const {
  for(int i = 0; i < 2; i++) robot.moveUntilLine(Direction::FRONT);
  for(int i = 0; i < NUM_LINES; i++) {
    robot.followUntilIntersection(follow_sequence[i]);
    coverLine(cover_sequence[i]);
  }
};
