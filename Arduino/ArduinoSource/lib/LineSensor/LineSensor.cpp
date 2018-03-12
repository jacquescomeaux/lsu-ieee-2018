#include <LineSensor.h>

#include <Arduino.h>

LineSensor::LineSensor() :
  NUM_PINS(32),
  OFFSET_TO_RAD(3.141592653589793 / 16),
  pins {
    30, 31, 32, 33, 34, 35, 36, 37,
    38, 39, 40, 41, 42, 43, 44, 45,
    46, 47, 48, 49, 50, 51, 52, 53,
    54, 55, 56, 57, 58, 59, 60, 61
  },
  qtrrc1(pins, NUM_PINS/2),
  qtrrc2(pins + NUM_PINS/2, NUM_PINS/2) {
    for(int i = 0; i < 32; i++) {
      SINES[i] = Fixed(sin(i * OFFSET_TO_RAD.getDouble()));
      COSINES[i] = Fixed(cos(i * OFFSET_TO_RAD.getDouble()));
    }
}

void LineSensor::calibrateSensors() {
  qtrrc1.calibrate();
  qtrrc2.calibrate();
}

Fixed LineSensor::getLinePosition(int offset, int range) {
  qtrrc1.readCalibrated(sensor_values);
  qtrrc2.readCalibrated(sensor_values + sizeof(unsigned int)*NUM_PINS/2);
  sensor_values[10] = 0;
  sensor_values[6] = 0;
  sensor_values[14] = 0;
  sensor_values[18] = 0;
  Fixed weighted = 0;
  Fixed total = 0;
  //for(int i = offset - range; i <= offset + range; i++) {
  for(int i = 0 - range; i <= range; i++) { 
    weighted += 1000 * i * sensor_values[i + offset % 32];
    total += sensor_values[i + offset % 32];
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
