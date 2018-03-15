#include <LineSensor.h>

#include <Arduino.h>
#include <stdint.h>

LineSensor::LineSensor() :
  NUM_PINS(32),
  line_threshold(500),
  OFFSET_TO_RAD(3.141592653589793 / 16),
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
      COSINES[i] = Fixed(cos(static_cast<double>(i) * OFFSET_TO_RAD.getDouble()));
    }
}

void LineSensor::readSensors() {
  qtrrc1.readCalibrated(sensor_values);
  qtrrc2.readCalibrated(&sensor_values[NUM_PINS/2]); 
}

Fixed LineSensor::getLinePosition(int offset, int range) {
  qtrrc1.readCalibrated(sensor_values);
  qtrrc2.readCalibrated(&sensor_values[NUM_PINS/2]);
  Fixed weighted = 0;
  Fixed total = 0;
  for(int32_t i = 0 - range; i <= range; i++) { 
    weighted +=  Fixed(1000) * Fixed(i) * Fixed(static_cast<int32_t>(sensor_values[i + offset % 32]));
    total += Fixed(static_cast<int32_t>(sensor_values[i + offset % 32]));
  }
  return weighted/total;
}

void LineSensor::calibrateSensors() {
  qtrrc1.calibrate();
  qtrrc2.calibrate();
}

void LineSensor::getLineErrors(Fixed* x, Fixed* y, Fixed* rot, Direction dir) {
  switch(dir) {
    case(Direction::NONE): break;
    case(Direction::FRONT): getLineErrors(x, y, rot, 8); break;
    case(Direction::BACK): getLineErrors(x, y, rot, /*24*/8); break;
    case(Direction::LEFT): getLineErrors(x, y, rot, 16); break;
    case(Direction::RIGHT): getLineErrors(x, y, rot, /* 0*/16); break;
    case(Direction::FRONT_LEFT): getLineErrors(x, y, rot, 12); break;
    case(Direction::FRONT_RIGHT): getLineErrors(x, y, rot, 4); break;
    case(Direction::BACK_LEFT): getLineErrors(x, y, rot, 4); break;
    case(Direction::BACK_RIGHT): getLineErrors(x, y, rot, 12); break;
    case(Direction::CLOCKWISE): break;
    case(Direction::COUNTER_CLOCKWISE): break;
    default: break; 
  }
}

void LineSensor::getLineErrors(Fixed* x, Fixed* y, Fixed* rot, int offset) {
  int fi = offset % 16;
  int li = ((offset - 8) % 16) + 8;
  Fixed f = getLinePosition(fi, 2);
  Fixed b = getLinePosition(fi + 16, 2);
  Fixed l = getLinePosition(li, 2);
  Fixed r = getLinePosition((li + 16) % 32, 2);
  *rot = (b + f) * SINES[offset] * SINES[offset]
       + (r + l) * COSINES[offset] * COSINES[offset];
  *x = (b - f) * SINES[offset];
  *y = (r - l) * COSINES[offset];
}

void LineSensor::getIntersectionErrors(Fixed* x, Fixed* y, Fixed* rot, int offset) {
  int fi = offset % 16;
  int li = (fi + 8) % 16 ;
  Fixed f = getLinePosition(fi, 3);
  Fixed b = getLinePosition(fi + 16, 3);
  Fixed l = getLinePosition(li, 3);
  Fixed r = getLinePosition((li + 16) % 32, 3);
  *rot = Fixed(0.5) * (b + f + r + l);
  *x = (b - f);
  *y = (r - l);
}

int LineSensor::countLinePeaks(int range) {
  readSensors();
  int peak_count = 0;
  for(int i = 0; i < NUM_PINS; i++) if(sensor_values[i] > line_threshold) {
    int higher_values_in_range = 0;
    for(int j = 0 - range; j <= range; j++) if(sensor_values[i] < sensor_values[i + j % NUM_PINS]) higher_values_in_range++;
    if(higher_values_in_range == 0) peak_count++;
  }
  return peak_count;
}

void LineSensor::printReadings() {
  readSensors();
  for(int i = 0; i < 4; i++) {
    for(int j = 0; j < 8; j++) {
      int k = i*8+j;
      Serial.print("S");
      if(k<10) Serial.print("0");
      Serial.print(k);
      Serial.print(": p");
      Serial.print(pins[k]);
      unsigned int v = values[k];
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
