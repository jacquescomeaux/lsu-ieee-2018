#include <Robot.h>

Robot::Robot() :
  stopped(true),
  center_offset(8),
  follow_range(2),
  flags(Flag::NONE),
  edge_detectors {
    ProximitySensor( 6,  7, 600, 750), //RIGHT(0)
    ProximitySensor( 8,  9, 500, 750), //FRONT(1)
    ProximitySensor(10, 11, 500, 800), //LEFT(2)
    ProximitySensor(12, 13, 500, 750)  //BACK(3)
  } {
    stop();
    pinMode(A8, INPUT);
    pinMode(A9, INPUT);
}

void Robot::checkEdges() {
  //for(ProximitySensor& s : edge_detectors) if(s.edgeDetected()) stop();

  /* COMMENTED OUT WORKING CODE */
  /*if(current_direction == Direction::FRONT) if(edge_detectors[1].edgeDetected()) stop();
  if(current_direction == Direction::BACK) if(edge_detectors[3].edgeDetected()) stop();
  if(current_direction == Direction::LEFT) if(edge_detectors[2].edgeDetected()) stop();
  if(current_direction == Direction::RIGHT) if(edge_detectors[0].edgeDetected()) stop();*/
}

void Robot::stop() {
  flags &= ~Flag::FOLLOWING_LINE;
  flags &= ~Flag::CENTERING_CROSS;
  flags &= ~Flag::CENTERING_CORNER;
  Drivetrain::stop();
  resetPIDData();
}

bool Robot::ready() {
  int go = digitalRead(A8);
  int stop = digitalRead(A9);
  if(go == HIGH) stopped = false;
  if(stop == HIGH) stopped = true;
  return !stopped;
}

void Robot::update() {
  static const int NUM_TASKS = 8;
  static unsigned long last_ran[NUM_TASKS] = {0};
  unsigned long dt[NUM_TASKS];
  unsigned long time = millis();
  for(int i = 0; i < NUM_TASKS; i++)  dt[i] = time - last_ran[i];
  
  if((dt[0] > 100) ? (last_ran[0] = time) : false) approachSpeed();

  if((dt[1] > 0) ? (last_ran[1] = time) : false) {
    if((flags & Flag::FOLLOWING_LINE) != Flag::NONE) {
      Fixed xcrr, ycrr, rcrr;
      getLineCorrections(&xcrr, &ycrr, &rcrr, resolveOffset(current_direction), follow_range);
      veer(xcrr, ycrr, rcrr);
    }
  }
  
  if((dt[2] > 10) ? (last_ran[2] = time) : false) {
    if((flags & Flag::CALIBRATING_LINE) != Flag::NONE) {
      calibrateSensors();
      //printCalibratedValues();
    }
  }
  
  if((dt[3] > 1000) ? (last_ran[3] = time) : false) {
    //if((flags & Flag::PRINTING_LINE) != Flag::NONE) printReadings();
  }
  
  if((dt[4] > 200) ? (last_ran[4] = time) : false) {
  //checkEdges();
  }
  
  if((dt[5] > 0) ? (last_ran[5] = time) : false) {
    if((flags & Flag::TRAVELLING) != Flag::NONE) flags &= ~Drivetrain::checkDestination((flags & Flag::STOP_AFTER_TRAVEL) != Flags::NONE);
  }
  
  if((dt[6] > 0) ? (last_ran[6] = time) : false) {
    if((flags & Flag::CENTERING_CROSS) != Flag::NONE) {
      Fixed xcrr, ycrr, rcrr;
      getCenterCorrections(&xcrr, &ycrr, &rcrr, true, center_offset);
      veer(xcrr, ycrr, rcrr);
    }
  }
  
  if((dt[7] > 0) ? (last_ran[7] = time) : false) {
    if((flags & Flag::CENTERING_CORNER) != Flag::NONE) {
      Fixed xcrr, ycrr, rcrr;
      getCenterCorrections(&xcrr, &ycrr, &rcrr, false, center_offset);
      veer(xcrr, ycrr, rcrr);
    }
  }
  
  if(!ready()) stop();
}

void Robot::travel(Direction dir, Fixed dist) {
  travel(dir, base_speed, dist);
}

void Robot::travel(Direction dir, Fixed speed, Fixed dist) {
  Fixed x, y, rot;
  resolveDirection(dir, &x, &y, &rot);
  travel(speed * x, speed * y, speed * rot, dist);
}

void Robot::travel(Fixed x, Fixed y, Fixed rot, Fixed dist) {
  flags |= Flag::TRAVELLING;
  Drivetrain::travel(x, y, rot, dist);
}

void Robot::nudge(Direction dir, Fixed dist) {
  Fixed x, y, rot;
  Fixed speed = 100;
  resolveDirection(dir, &x, &y, &rot);
  nudge(speed * x, speed * y, speed * rot, dist);
}

void Drivetrain::nudge(Fixed x, Fixed y, Fixed rot, Fixed dist) {
  flags |= Flag::TRAVELLING;
  Drivetrain::nudge(x, y, rot, dist);
}


void Robot::setFlags(Flag settings) {
  flags |= settings;
}

void Robot::clearFlags(Flag settings) {
  flags &= ~settings;
}

void Robot::toggle(Flag settings) {
  settings &= ~Flag::NONE;
  flags ^= settings;
  
  //R.I.P.
  if((flags & settings & Flag::CALIBRATING_LINE) != Flag::NONE); // Serial.println("CALIBRATING_LINE set");  
  if((~flags & settings & Flag::CALIBRATING_LINE) != Flag::NONE); // Serial.println("CALIBRATING_LINE cleared");  
  if((flags & settings & Flag::FOLLOWING_LINE) != Flag::NONE); // Serial.println("FOLLOWING_LINE set"); 
  if((~flags & settings & Flag::FOLLOWING_LINE) != Flag::NONE); // Serial.println("FOLLOWING_LINE cleared"); 
  if((flags & settings & Flag::PRINTING_LINE) != Flag::NONE); // Serial.println("PRINTING_LINE set"); 
  if((~flags & settings & Flag::PRINTING_LINE) != Flag::NONE); // Serial.println("PRINTING_LINE cleared"); 
  if((flags & settings & Flag::STOPPING_INT) != Flag::NONE); // Serial.println("STOPPING_INT set"); 
  if((~flags & settings & Flag::STOPPING_INT) != Flag::NONE); // Serial.println("STOPPING_INT cleared"); 
  if((flags & settings & Flag::CENTERING_CROSS) != Flag::NONE); // Serial.println("CENTERING_CROSS set"); 
  if((~flags & settings & Flag::CENTERING_CROSS) != Flag::NONE); // Serial.println("CENTERING_CROSS cleared"); 
  if((flags & settings & Flag::CENTERING_CORNER) != Flag::NONE); // Serial.println("CENTERING_CORNER set"); 
  if((~flags & settings & Flag::CENTERING_CORNER) != Flag::NONE); // Serial.println("CENTERING_CORNER cleared"); 
}

void Robot::setCenterOffset(unsigned int offset) {
  center_offset = offset;
}

void Robot::setFollowRange(unsigned int range) {
  follow_range = range;
}

void Robot::setTravelStop(bool stopping) {
  if(stopping) flags |= Flag::STOP_AFTER_TRAVEL;
  else flags &= ~Flag::STOP_AFTER_TRAVEL;
}

SortBot::SortBot() {}

void SortBot::update() {
  continueSorting();
  Robot::update();
}

void SortBot::stop() {
  Robot::stop();
}
