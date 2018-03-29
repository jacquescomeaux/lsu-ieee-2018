#include <LineSensor.h>

#include <Arduino.h>
#include <stdint.h>

LineSensor::LineSensor() :
  NUM_PINS(32),
  line_threshold(500),
  OFFSET_TO_RAD(3.141592653589793 / static_cast<double>(16)),
  pins {
    22, 23, 24, 25, 26, 27, 28, 29,
    30, 31, 32, 33, 34, 35, 36, 37,
    38, 39, 40, 41, 42, 43, 44, 45,
    46, 47, 48, 49, 50, 51, 52, 53
  },
  qtrrc1(pins, NUM_PINS/2),
  qtrrc2(&pins[NUM_PINS/2], NUM_PINS/2) {
    for(int i = 0; i < 32; i++) {
      SINES[i] = Fixed(sin(static_cast<double>(i) * OFFSET_TO_RAD.getDouble()));
      Serial.print("sines ");
      Serial.println(SINES[i].getDouble());
      COSINES[i] = Fixed(cos(static_cast<double>(i) * OFFSET_TO_RAD.getDouble()));
      Serial.print("cosines ");
      Serial.println(COSINES[i].getDouble());
    }
}

void LineSensor::readSensors() {
  qtrrc1.readCalibrated(sensor_values);
  qtrrc2.readCalibrated(&sensor_values[NUM_PINS/2]); 
}

Fixed LineSensor::getLinePosition(int offset, int range, bool along_arc) {
  Fixed weighted = 0;
  Fixed total = 0;
  for(int32_t i = 0 - range; i <= range; i++) {
    Fixed pos = along_arc ? i : SINES[(i + 32) % 32];
    weighted +=  Fixed(1000) * pos * Fixed(static_cast<int32_t>(sensor_values[(i + offset + 32) % 32]));
    total += Fixed(static_cast<int32_t>(sensor_values[(i + offset + 32) % 32]));
  }
  return weighted/total;
}

void LineSensor::calibrateSensors() {
  qtrrc1.calibrate();
  qtrrc2.calibrate();
}

void LineSensor::getLineErrors(Fixed* x, Fixed* y, Fixed* rot, Direction dir, int range) {
  switch(dir) {
    case(Direction::NONE): break;
    case(Direction::FRONT): getLineErrors(x, y, rot, 8, range); break;
    case(Direction::BACK): getLineErrors(x, y, rot, 24, range); break;
    case(Direction::LEFT): getLineErrors(x, y, rot, 16, range); break;
    case(Direction::RIGHT): getLineErrors(x, y, rot, 0, range); break;
    case(Direction::FRONT_LEFT): getLineErrors(x, y, rot, 12, range); break;
    case(Direction::FRONT_RIGHT): getLineErrors(x, y, rot, 4, range); break;
    case(Direction::BACK_LEFT): getLineErrors(x, y, rot, 20, range); break;
    case(Direction::BACK_RIGHT): getLineErrors(x, y, rot, 28, range); break;
    case(Direction::CLOCKWISE): break;
    case(Direction::COUNTER_CLOCKWISE): break;
    default: break; 
  }
}

void LineSensor::getLineErrors(Fixed* x, Fixed* y, Fixed* rot, int offset, int range) {
  readSensors();
  int fi = offset % 16;
  int bi = fi + 16;
  int li = ((offset + 24) % 16) + 8;
  int ri = (li + 16) % 32;
  Fixed f = getLinePosition(fi, range, true);
  Fixed b = getLinePosition(bi, range, true);
  Fixed l = getLinePosition(li, range, true);
  Fixed r = getLinePosition(ri, range, true);
  *rot = (b + f) * SINES[fi] * SINES[fi]
       + (r + l) * COSINES[ri] * COSINES[ri];
  f = getLinePosition(fi, range, false);
  b = getLinePosition(bi, range, false);
  l = getLinePosition(li, range, false);
  r = getLinePosition(ri, range, false);
  *x = (b - f) * SINES[fi];
  *y = (r - l)  * COSINES[ri];

  /*Serial.print("getLineErrors() ");
  printErrors(*x, *y, *rot);
  */
}

void LineSensor::getCrossIntersectionErrors(Fixed* x, Fixed* y, Fixed* rot, int offset) {
  Fixed x_p, y_p, rot_p, x_s, y_s, rot_s;
  getLineErrors(&x_p, &y_p, &rot_p, offset, 4);
  getLineErrors(&x_s, &y_s, &rot_s, (offset + 8) % 32, 4);
  *x = x_p + x_s;
  *y = y_p + y_s;
  *rot = SINES[4] * SINES[4] * (rot_p + rot_s);

  //Serial.print("getCrossIntersectionErrors() ");
  //printErrors(*x, *y, *rot);
}

void LineSensor::getCornerIntersectionErrors(Fixed* x, Fixed* y, Fixed* rot, int offset) {
  int bi = (offset + 16) % 32;
  int di = (bi + 4) % 32;
  Fixed x_d, y_d, rot_d;
  getLineErrors(&x_d, &y_d, &rot_d, di, 2);
  //Serial.print("b:");
  //Serial.println(bi);
  Fixed b = getLinePosition(bi % 32, 2, true);

//begin test code
 /*int front = 8;
 int back = 8 + 16;
 int backleft = back - 4;
 int backright = back + 4;
 Fixed xf, yf, rotf, xb, yb, rotb, xbl, ybl, rotbl, xbr, ybr, rotbr;

 getLineErrors(&xf, &yf, &rotf, front, 2);
 getLineErrors(&xb, &yb, &rotb, back, 0);
 getLineErrors(&xbl, &ybl, &rotbl, backleft, 2);
 getLineErrors(&xbr, &ybr, &rotbr, backright, 2); //Does larger range result in larger weight?

 *x = xf + xbl + xbr;
 *y = yf + ybl + ybr;
 *rot = (rotf + rotbl + rotbr) * SINES[16] * SINES[24];
*/
//end test code

  *x = x_d + b * COSINES[di];// + r * COSINES[(di + 16) % 32];
  *y = y_d + b * SINES[di];// + r * SINES[(di + 16) % 32];
  *rot = rot_d;

  //Serial.print("getCornerIntersectionErrors ");
  //printErrors(*x, *y, *rot);
}

int LineSensor::countLinePeaks(int range) {
  readSensors();
  int peak_count = 0;
  for(int i = 0; i < NUM_PINS; i++) if(sensor_values[i] > line_threshold) {
    int higher_values_in_range = 0;
    for(int j = 0 - range; j <= range; j++) if(sensor_values[i] < sensor_values[(i + j + NUM_PINS) % NUM_PINS]) higher_values_in_range++;
    if(higher_values_in_range == 0) peak_count++;
  }
  return peak_count;
}

void LineSensor::precalibrate(int min = 280, int max = 4000) { //don't use this, it breaks things
  unsigned int* front_mins = qtrrc1.calibratedMinimumOn;
  unsigned int* back_mins = qtrrc2.calibratedMinimumOn;
  unsigned int* front_maxs = qtrrc1.calibratedMinimumOn;
  unsigned int* back_maxs = qtrrc2.calibratedMinimumOn;

  for (int i = 0; i < 16; i++) {
    front_mins[i] = min;
    back_mins[i] = min;
    front_maxs[i] = max;
    back_maxs[i] = max;
  }
}

void LineSensor::printReadings() {
  readSensors();
  unsigned int total = 0;
  for(unsigned int v : sensor_values) total += v;
  Serial.print("Total line: ");
  Serial.println(total);
  unsigned int* front_mins = qtrrc1.calibratedMinimumOn;
  unsigned int* back_mins = qtrrc2.calibratedMinimumOn;
  unsigned int* front_maxs = qtrrc1.calibratedMaximumOn;
  unsigned int* back_maxs = qtrrc2.calibratedMaximumOn;
  for(int i = 0; i < 16; i++) {
    Serial.print(front_mins[i]);
    Serial.print(" ");
  }
  for(int i = 0; i < 16; i++) {
    Serial.print(back_mins[i]);
    Serial.print(" ");
  }
  Serial.println();
  for(int i = 0; i < 16; i++) {
    Serial.print(front_maxs[i]);
    Serial.print(" ");
  }
  for(int i = 0; i < 16; i++) {
    Serial.print(back_maxs[i]);
    Serial.print(" ");
  }
  Serial.println();
  for(int i = 0; i < 4; i++) {
    for(int j = 0; j < 8; j++) {
      int k = i*8+j;
      Serial.print("S");
      if(k<10) Serial.print("0");
      Serial.print(k);
      Serial.print(": p");
      Serial.print(pins[k]);
      unsigned int v = sensor_values[k];
      Serial.print(" v: ");
      if(v < 1000) Serial.print(" "); 
      if(v < 100) Serial.print(" "); 
      if(v < 10) Serial.print(" "); 
      Serial.print(v);
      Serial.print("   ");
    }
    Serial.println("");
  }
  Serial.println("\n------------------------------------------------------------------------------------------------");
}

void LineSensor::printLinePeaks() {
  Serial.print("Lines Seen: ");
  Serial.println(countLinePeaks(3));
}

void LineSensor::printCalibratedValues() {
  long min = 1000;
  long max = 0;
  long testval = 0;

  for(int i = 0; i < 16; i++) {
    testval = qtrrc1.calibratedMinimumOn[i];
    if (testval < min) min = testval;
    testval = qtrrc2.calibratedMinimumOn[i];
    if (testval < min) min = testval;

   testval = qtrrc1.calibratedMaximumOn[i];
   if (testval > max) max = testval;
   testval = qtrrc2.calibratedMaximumOn[i];
   if (testval > max) max = testval;
  }

  Serial.print("Calibrated Values (min,max) : (");
  Serial.print(min);
  Serial.print(",");
  Serial.print(max);
  Serial.println(")");
}

void LineSensor::printErrors(Fixed x, Fixed y, Fixed rot) {
  Serial.print("Errors (x, y, rot): (");
  Serial.print(x.getInt());
  Serial.print(" , ");
  Serial.print(y.getInt());
  Serial.print(" , ");
  Serial.print(rot.getInt());
  Serial.println(" )");
}
