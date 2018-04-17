#include <LineFollower.h>

LineFollower::LineFollower() :
  pid_terms {
    //Proportional //Integral    //Derivitave  //Accum.  //Last error
    {Fixed(0.060), Fixed(0.010), Fixed(0.300), Fixed(0), Fixed(0)}, //x
    {Fixed(0.060), Fixed(0.002), Fixed(0.100), Fixed(0), Fixed(0)}, //y
    {Fixed(0.020), Fixed(0.0005), Fixed(0.070), Fixed(0), Fixed(0)},//rot
  },
  array_filled(false),
  line_sensor() {}

void LineFollower::calibrateSensors() {
  line_sensor.calibrateSensors();
}

void LineFollower::correctErrors(Fixed xerr, Fixed yerr, Fixed rerr, Fixed* xcrr, Fixed* ycrr, Fixed* rcrr) {
  static const Fixed FIFTH = 0.2;
  static unsigned long t = 0;
  static Fixed prev_errors[3][5] = {0};
  prev_errors[0][t] = xerr;
  prev_errors[1][t] = yerr;
  prev_errors[2][t] = rerr;
  Fixed avgs[3];
  for(int i = 0; i < 3; i++) {
    for(Fixed f : prev_errors[i]) avgs[i] += f;
    avgs[i] *= FIFTH;
  }
  if(array_filled) {
    //PID CONTROLLER
    //         KP * current error        +  KI * accumulated error             +  KD * change in error
    *xcrr = (pid_terms[0][0]  * avgs[0]) + (pid_terms[0][1] * pid_terms[0][3]) + (pid_terms[0][2] * (avgs[0] - pid_terms[0][4])); //x correction
    *ycrr = (pid_terms[1][0]  * avgs[1]) + (pid_terms[1][1] * pid_terms[1][3]) + (pid_terms[1][2] * (avgs[1] - pid_terms[1][4])); //y correction
    *rcrr = (pid_terms[2][0]  * avgs[2]) + (pid_terms[2][1] * pid_terms[2][3]) + (pid_terms[2][2] * (avgs[2] - pid_terms[2][4]));  //rot correction
  }
  pid_terms[0][3] += xerr;
  pid_terms[1][3] += yerr;
  pid_terms[2][3] += rerr;
  pid_terms[0][4]  = avgs[0];
  pid_terms[1][4]  = avgs[1];
  pid_terms[2][4]  = avgs[2];
  if(++t >= 5) {
    t = 0;
    array_filled = true;
  }
}

void LineFollower::getCenterCorrections(Fixed* x, Fixed* y, Fixed* rot/*, bool cross, unsigned int offset*/) {
  Fixed xerr, yerr, rerr;
  line_sensor.getIntersectionErrors(&xerr, &yerr, &rerr);
  //if(cross) line_sensor.getCrossIntersectionErrors(&xerr, &yerr, &rerr, offset);
  //else line_sensor.getCornerIntersectionErrors(&xerr, &yerr, &rerr, offset);
  correctErrors(xerr, yerr, rerr, x, y, rot);
}

void LineFollower::getLineCorrections(Fixed* x, Fixed* y, Fixed* rot, unsigned int offset, unsigned int range) {
  Fixed xerr, yerr, rerr;
  line_sensor.getLineErrors(&xerr, &yerr, &rerr, offset, range);
  correctErrors(xerr, yerr, rerr, x, y, rot);
}

void LineFollower::adjustPID(unsigned int var, unsigned int term, Fixed adjustment) {
  if(var > 2 || term > 2) return;
  pid_terms[var][term] += adjustment;
  /* if(var == 0) Serial.print("X");
  if(var == 1) Serial.print("Y");
  if(var == 2) Serial.print("Rot");
  if(term == 0) Serial.print("P = ");
  if(term == 1) Serial.print("I = ");
  if(term == 2) Serial.print("D = ");
  Serial.println(pid_terms[var][term].getDouble(), 4);*/
}

void LineFollower::resetPIDData() {
  for(int i = 0; i < 3; i++) for(int j = 3; j < 5; j++) pid_terms[i][j] = Fixed(0);
  array_filled = false;
}
