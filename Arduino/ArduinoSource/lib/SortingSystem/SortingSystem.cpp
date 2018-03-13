#include "SortingSystem.h"

SortingSystem::SortingSystem(Adafruit_StepperMotor* arm_motor, Adafruit_StepperMotor* plate_motor) :
  NUM_COLORS(8),
  COLOR_POSITIONS {0, 6, 5, 4, 1, 2, 3, 7},
  state(0),
  token_arm(arm_motor),
  storage_plate(plate_motor) {}

void SortingSystem::pickUpToken() {
  //token_arm.pickUpToken();
  task_buffer.push(9);
}

void SortingSystem::storeToken(Color c) {
  task_buffer.push(static_cast<int>(c));
}

void SortingSystem::dropNextTokenStack() {
  task_buffer.push(10);
}

void SortingSystem::continueSorting() {
  if(task_buffer.empty()) return;
  int current_task = task_buffer.front(); 
  if(current_task == 9) {
    token_arm.pickUpToken();
    task_buffer.pop();
  }
  else if(current_task == 10) {
    storage_plate.rotateCCW();
    task_buffer.pop();
  }
  else {
    int pos = COLOR_POSITIONS[current_task];
    if(state == 0) {
      if(storage_plate.ready()) storage_plate.rotateCW(pos);
      else state += storage_plate.continueMoving();
    }
    else if(state == 1) {
      //if(token_arm.ready()) token_arm.storeToken();
      //else state += token_arm.continueMoving();
      state++;
    }
    else if(state == 2) {
      if(storage_plate.ready()) storage_plate.rotateCW(8 - pos);
      else state += storage_plate.continueMoving();
    }
    else {
      state = 0;
      task_buffer.pop();
    }
  }
}
