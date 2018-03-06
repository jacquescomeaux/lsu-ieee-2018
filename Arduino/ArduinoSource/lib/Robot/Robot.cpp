#include <Robot.h>
//#include <vector>

Robot::Robot() :
  flags(Flag::NONE),
  NUM_TASKS(6),
  KP(Fixed(0.03)),
  KD(Fixed(0.00)),
  base_speed(Fixed(90)),
  veer_amount(Fixed(10)),
  acceleration(Fixed(3)),
  motor_shields {
    MotorShield(0x61),
    MotorShield(0x62)
  },
  wheels {
    Wheel(motor_shields[0].getMotor(1), 2, 4), //Interrupt Pins: 2, 3, 18, 19, 20, 21
    Wheel(motor_shields[0].getMotor(2), 3, 5),
    Wheel(motor_shields[1].getMotor(1), 18, 22),
    Wheel(motor_shields[1].getMotor(2), 19, 23)
  },
  /*edge_detectors {
    ProximitySensor(5, 6),
    ProximitySensor(0, 0),
    ProximitySensor(0, 0),
    ProximitySensor(0, 0)
  },*/
  //line_sensor(30, 32),
  KP_ptr(&KP), 
  KD_ptr(&KD)//,
  {//base_speed_ptr(&base_speed) {
  stop();
} 

void Robot::checkEdges() {
  //for(const ProximitySensor& s : edge_detectors) if(s.edgeDetected()) stop();
//  if(edge_detectors[0].edgeDetected()) stop();
  //Serial.println(edge_detectors[0].getProximity());
}

void Robot::setWheelSpeeds(const Fixed* speeds) {
  for(int i = 0; i < 4; i++) Serial.println(speeds[i].getInt());//wheels[i].setSpeed(speeds[i]);
  for(int i = 0; i < 4; i++) wheels[i].setSpeed(speeds[i]);
}

void Robot::adjustWheelSpeeds(const Fixed* speeds) {
  for(int i = 0; i < 4; i++) wheels[i].adjustSpeed(speeds[i]);
}

/*void Robot::correctErrors() {
  int error = line_sensors[static_cast<int>(current_direction)].getLineError();  
  int adjustment = KP * error + KD * (error - last_error);
  last_error = error;
  for(int i = 0; i < 4; i++) wheels[i].adjustSpeed((i<2)?adjustment:-adjustment);
}*/

void Robot::stop() {
  for(Wheel& w : wheels) w.stop();
  flags &= ~Flag::FOLLOWING_LINE;
}

void Robot::update() {
  int dt[NUM_TASKS];
  int time = millis();
  //static std::vector<int> last_time = {0, 0, 0, 0, 0};
  static int last_time[5] =  {0, 0, 0, 0, 0};
  for(int i = 0; i < NUM_TASKS; i++)  dt[i] = time - last_time[i];
  if((dt[0] > 100) ? (last_time[0] = time) : false) for(Wheel& w : wheels) w.approachSpeed(acceleration);
  if((dt[1] > 100) ? (last_time[1] = time) : false) if((flags & Flag::FOLLOWING_LINE) != Flag::NONE) ;//correctErrors();
  if((dt[2] > 100) ? (last_time[2] = time) : false) if((flags & Flag::CALIBRATING_LINE) != Flag::NONE) ;//for(LineSensor& l : line_sensors) l.calibrateSensors();
  if((dt[3] > 100) ? (last_time[3] = time) : false) if((flags & Flag::PRINTING_LINE) != Flag::NONE) ;//line_sensors[static_cast<int>(current_direction)].printReadings(); 
  if((dt[4] > 100) ? (last_time[4] = time) : false) checkEdges();
  if((dt[5] > 100) ? (last_time[5] = time) : false) checkDestination(); //check if robot has reached destination
}

void Robot::move(Direction dir) {
  move(dir, base_speed);
}

void Robot::move(Direction dir, Fixed speed) {
  switch(dir) {
    case(Direction::NONE): stop(); break;
    case(Direction::FRONT): move(Fixed(0), speed, Fixed(0)); break;
    case(Direction::BACK): move(Fixed(0), Fixed(0) - speed, Fixed(0)); break;
    case(Direction::LEFT): move(Fixed(0), speed, Fixed(0)); break;
    case(Direction::RIGHT): move(Fixed(0), Fixed(0) - speed, Fixed(0)); break;
    case(Direction::FRONT_LEFT): move(Fixed(0) - speed/2, speed/2, Fixed(0)); break;
    case(Direction::FRONT_RIGHT): move(speed/2, speed/2, Fixed(0)); break;
    case(Direction::BACK_LEFT): move(Fixed(0) - speed/2, Fixed(0) - speed/2, Fixed(0)); break;
    case(Direction::BACK_RIGHT): move(speed/2, Fixed(0) - speed/2, Fixed(0)); break;
    case(Direction::CLOCKWISE): move(Fixed(0), Fixed(0), speed); break;
    case(Direction::COUNTER_CLOCKWISE): move(Fixed(0), Fixed(0), Fixed(0) - speed); break;
    default: stop();
  }
}

void Robot::move(Fixed x, Fixed y, Fixed rot) {
  flags &= ~Flag::FOLLOWING_LINE;
  const Fixed speeds[4] = {y + x - rot, y - x - rot, y + x + rot, y - x + rot};
  setWheelSpeeds(speeds);
}

void Robot::moveSetDistance(Direction dir, int distance) { 
	long stepsToTravel = distance * 287; //286.7 steps per inch
	
	for(int i = 0; i < 4; i++) {
		currentWheelPosition[i] = wheels[i].getPosition();
		targetWheelPosition[i] = currentWheelPosition[i] + stepsToTravel;
	}
	
	flags |= Flag::TRAVEL_TO_DST;
	move(dir, base_speed);//need to fix speed argument
}

void Robot::checkDestination() {
	//int wheelDestinationReached = 0; //counter to see if all wheels have reached destination..testing needed
	for(int i = 0; i < 4; i++) {
		currentWheelPosition[i] = wheels[i].getPosition();
		
		//Debug Serial Printing
		Serial.print("Wheel ");
		Serial.print(i);
		Serial.print(" has ");
		Serial.print(targetWheelPosition[i] - currentWheelPosition[i]);
		Serial.println(" steps remaining.");
		
		if (currentWheelPosition[i] >= targetWheelPosition[i]) {
			flags &= ~Flag::TRAVEL_TO_DST; //end moveSetDistance
			(stop); //stop all wheels once 1 wheel has gone desired distance
		}
	}
}

/*void Robot::followLine(Direction dir) {
  //Serial.println("call to follow");//
  followLine(dir, default_speed);
}

void Robot::followLine(Direction dir, int speed) {
  following_line = true;
  setWheelSpeeds(dir, speed);
}*/

void Robot::veer(Direction dir) {
  veer(dir, veer_amount);
}

void Robot::veer(Direction dir, Fixed amount) {
  switch(dir) {
    case(Direction::NONE): break;
    case(Direction::FRONT): veer(Fixed(0), amount, Fixed(0)); break;
    case(Direction::BACK): veer(Fixed(0), Fixed(0) - amount, Fixed(0)); break;
    case(Direction::LEFT): veer(Fixed(0), amount, Fixed(0)); break;
    case(Direction::RIGHT): veer(Fixed(0), Fixed(0) - amount, Fixed(0)); break;
    case(Direction::FRONT_LEFT): veer(Fixed(0) - amount/2, amount/2, Fixed(0)); break;
    case(Direction::FRONT_RIGHT): veer(amount/2, amount/2, Fixed(0)); break;
    case(Direction::BACK_LEFT): veer(Fixed(0) - amount/2, Fixed(0) - amount/2, Fixed(0)); break;
    case(Direction::BACK_RIGHT): veer(amount/2, Fixed(0) - amount/2, Fixed(0)); break;
    case(Direction::CLOCKWISE): veer(Fixed(0), Fixed(0), amount); break;
    case(Direction::COUNTER_CLOCKWISE): veer(Fixed(0), Fixed(0), Fixed(0) - amount); break;
    default: break; 
  }
}

void Robot::veer(Fixed x, Fixed y, Fixed rot) {
  flags &= ~Flag::FOLLOWING_LINE;
  const Fixed adjustments[4] = {y + x - rot, y - x - rot, y + x + rot, y - x + rot};
  adjustWheelSpeeds(adjustments);
}


/*void Robot::toggle(Flag setting) {
  toggleMultiple(setting);
  //if(calibrating) Serial.println("Begin Calibration");
  //else Serial.println("End Calibration");
  //if(calibrating) Serial.println("Begin Calibration");
  //else Serial.println("End Calibration");
  //if(edges) Serial.println("Begin Output edges");
  //else Serial.println("End Output edges");
}*/

void Robot::toggleMultiple(Flag settings) {
  settings &= ~Flag::NONE;
  settings &= ~Flag::FOLLOWING_LINE;
  flags ^= settings; 
}

void Robot::adjustParameter(Fixed* const param, Fixed adjustment) {
  *param += adjustment;
  //Serial.print("Speed = ");
  //Serial.println(default_speed);
}

SortBot::SortBot() {}

