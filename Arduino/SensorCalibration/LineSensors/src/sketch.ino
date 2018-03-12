#include <QTRSensors.h>

const int NUM_SENSORS = 32;
const unsigned char PIN_START;
QTRSensorsRC qtrrc;
unsigned int values[NUM_SENSORS];
unsigned char pins[NUM_SENSORS];

void setup() {
  for(unsigned char i = 0; i < NUM_SENSORS; i++) pins[i] = static_cast<unsigned char>(PIN_START + i);
  qtrrc = QTRSensorsRC(pins, NUM_SENSORS);
  Serial.begin(9600);
}

void loop() {
  qtrrc.read(values);
  for(int i = 0; i < 4; i++) {
    for(int j = 0; j < 8; j++) {
      Serial.print("S");
      Serial.print(i*j);
      Serial.print(": ");
      values[i*j];
      Serial.print("  ");
    }
    Serial.println();
  }
  delay(1000);
}
