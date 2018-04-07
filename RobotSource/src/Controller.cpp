#include "../include/Controller.h"
#include "../include/Robot.h"

#include <chrono>
#include <thread>
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
  dist_sequence {11.5, 6, 11.5, 11.5, 6, 11.5},
  travel_sequence {16, 3, 16, 12, 16, 3},
  blind_sequence {22, 11, 22, 22, 11, 22},
  drop_sequence {
    Direction::BACK_RIGHT,
    Direction::RIGHT,
    Direction::FRONT_RIGHT,
    Direction::FRONT_LEFT,
    Direction::LEFT,
    Direction::BACK_LEFT
  },
  box_sequence {
    Direction::FRONT,
    Direction::FRONT,
    Direction::LEFT,
    Direction::BACK,
    Direction::BACK
  } {}

Controller::Controller(SortBot& r, Direction* f_seq, Direction* c_seq, int n) :
  robot(r),
  NUM_LINES(n),
  follow_sequence(f_seq, f_seq + n),
  cover_sequence(c_seq, c_seq + n) {}

void Controller::coverLine(Direction dir, bool cross, int offset, int num_tokens, double dist) const {
  for(int i = 0; i < num_tokens; i++) {
    waitForEnter();
    for(int i = 0; i < 15; i++) {
      if(robot.center(cross, offset)) {
        if(robot.tokenSeen()) robot.sortToken();
        else std::cout << "token not seen" << std::endl;
        break;
      }
      if(i != 0) robot.travel(dir, 60, 0.4, true);
    }   
    //robot.snapToLine(dir, cross ? 3 : 1);
    if(i == num_tokens - 1) break;
    waitForEnter();
    robot.followLine(dir);
    robot.travel(dir, 60, dist, true);
  }
}

void Controller::waitForEnter() const {
  getchar();
}

void Controller::runAlgorithm() const {
  std::this_thread::sleep_for(std::chrono::seconds(5)); //prev 6 secs

  std::cout << "Waiting for enter key" << std::endl; 
  waitForEnter();
  #if 1
  while(true) {
   robot.center(false, 16);
   robot.sortToken();
   waitForEnter();
  }
  #else 
  robot.setSpeed(30);
  robot.toggleCalibration();
  robot.travel(Direction::FRONT, 30, 12, true);
  robot.snapToLine(Direction::LEFT, 6);
  robot.travel(Direction::CLOCKWISE, 70, 54, true);
  robot.toggleCalibration();
  
  robot.setSpeed(100);
  robot.snapToLine(Direction::LEFT, 6);
  
  robot.setSpeed(60);
  
  robot.followLine(Direction::RIGHT);
  robot.travel(Direction::RIGHT, 70, 16, false);
  robot.followUntilIntersection(Direction::RIGHT);
  /*for(int i = 0; i < NUM_LINES; i++) {
    robot.followLine(follow_sequence[i]);
    robot.travel(follow_sequence[i], 70, travel_sequence[i], false);
    robot.followUntilIntersection(follow_sequence[i]);
    coverLine(cover_sequence[i], type_sequence[i], offset_sequence[i], 4, dist_sequence[i]);
  }*/

  for(int i = 0; i < NUM_LINES; i++) {
    robot.travel(drop_sequence[i], 90, blind_sequence[i], true);
    robot.dropTokenStack(Color::RED);
    if(i == 5) break;
    robot.travel(box_sequence[i], 90, 10, true);
    robot.moveUntilLine(drop_sequence[(i+3)%6], 90);
    //robot.travel(drop_sequence[i], 60, -1 * blind_sequence[i], true);
    
    ////robot.center(type_sequence[i], offset_sequence[5-i]);
    ////robot.snapToLine(drop_sequence[(i+3)%6], 7);
    
    robot.snapToLine(box_sequence[i], 5);
    
    robot.followLine(box_sequence[i]);
    robot.travel(box_sequence[i], 90, 8, false);
    robot.followUntilIntersection(box_sequence[i]);
    robot.center(type_sequence[i], offset_sequence[5-i]);
  }

  //robot.travel(Direction::FRONT_RIGHT, 50, 48, true);
  robot.travel(Direction::FRONT_RIGHT, 60, 16, true);
  for(int i = 0; i < 5; i++) {
    robot.followUntilIntersection(Direction::FRONT_RIGHT);
    robot.followLine(Direction::FRONT_RIGHT);
    robot.travel(Direction::FRONT_RIGHT, 60, 6, false);
  }
  robot.dropTokenStack(Color::RED);
  #endif
}
