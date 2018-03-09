#include <LineSensor.h>

#include <Arduino.h>

/*LineSensor::LineSensor(unsigned char* p) :
  pins {p[0], p[1], p[2]},
  qtrrc(pins, 3),
  sensorValues {0, 0, 0} {} 

LineSensor::LineSensor(unsigned char p1, unsigned char p2, unsigned char p3) :
  pins {p1, p2, p3},
  qtrrc(pins, 3),
  sensorValues {0, 0, 0} {} 
*/

LineSensor::LineSensor(unsigned char pin_start) : NUM_PINS(32) {
  for(int i = 0; i < NUM_PINS; i++) pins[i] = static_cast<unsigned char>(pin_start + i);
  qtrrc.init(pins);
  for(int i = 0; i < NUM_PINS; i++) {
    SINES[i] = Fixed(sin(i * OFFSET_TO_RAD));
    COSINES[i] = Fixed(cos(i * OFFSET_TO_RAD));
  }
}

void LineSensor::calibrateSensors() {
  qtrrc.calibrate();
}

Fixed getLinePosition(int offset, int range) {
  qtrrc.readLineCalibrated(sensor_values);
  Fixed weighted = 0;
  Fixed total = 0;
  for(int i = offset - range; i <= offset + range; i++) {
    weighted += 1000 * i * sensor_values[i % 32];
    total += sensor_values[i % 32];
  }
  return weighted / total;
}

void LineSensor::getLineErrors(Fixed* x, Fixed* y, Fixed* rot, Direction dir) {
  switch(dir) {
    case(Direction::NONE): break;
    case(Direction::FRONT): getLineErrors(x, y, rot, 8); break;
    case(Direction::BACK): getLineErrors(x, y, rot, 16); break;
    case(Direction::LEFT): getLineErrors(x, y, rot, 24); break;
    case(Direction::RIGHT): getLineErrors(x, y, rot, 0); break;
    case(Direction::FRONT_LEFT): getLineErrors(x, y, rot, 12); break;
    case(Direction::FRONT_RIGHT): getLineErrors(x, y, rot, 4); break;
    case(Direction::BACK_LEFT): getLineErrors(x, y, rot, 20); break;
    case(Direction::BACK_RIGHT): getLineErrors(x, y, rot, 28); break;
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

/*void LineSensor::printReadings() {
  qtrrc.readCalibrated(sensorValues);
  Serial.print("left=");
  Serial.println(sensorValues[0]);
  Serial.print("middle=");
  Serial.println(sensorValues[1]);
  Serial.print("right=");
  Serial.println(sensorValues[2]);
}*/
