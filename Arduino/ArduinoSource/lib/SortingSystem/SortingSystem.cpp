#include "SortingSystem.h"

SortingSystem::SortingSystem(Adafruit_StepperMotor* arm_motor, Adafruit_DCMotor* magnet, Adafruit_StepperMotor* plate_motor) :
  NUM_COLORS(8),
  COLOR_POSITIONS {0, 4, 5, 6, 3, 2, 1, 7},
  state(0),
  token_arm(arm_motor, magnet),
  storage_plate(plate_motor) {
    token_arm.reset();
  }

void SortingSystem::pickUpToken() {
  //Serial.println("picking up token my man");
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
    storage_plate.rotateCW();
    task_buffer.pop();
  }
  else {
    int pos = COLOR_POSITIONS[current_task];
    if(state == 0) {
      if(storage_plate.ready()) storage_plate.rotateCCW(pos);
      else state += storage_plate.continueMoving();
    }
    else if(state == 1) {
      delay(20);
      token_arm.storeToken();
      state++;
    }
    else if(state == 2) {
      if(storage_plate.ready()) storage_plate.rotateCCW(NUM_COLORS - pos);
      else state += storage_plate.continueMoving();
    }
    else {
      state = 0;
      task_buffer.pop();
    }
  }
}
