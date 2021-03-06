#include <LineSensor.h>

#include <Arduino.h>
#include <stdint.h>

LineSensor::LineSensor() :
  NUM_PINS(32),
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
      COSINES[i] = Fixed(cos(static_cast<double>(i) * OFFSET_TO_RAD.getDouble()));
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
}
