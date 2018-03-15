#include <QTRSensors.h>

const unsigned char NUM_SENSORS = 32;
const unsigned char PIN_START = 22;
QTRSensorsRC* qtrrc1, * qtrrc2;
unsigned int values[NUM_SENSORS];
unsigned char pins[NUM_SENSORS];

void setup() {
  for(unsigned char i = 0; i < NUM_SENSORS; i++) pins[i] = static_cast<unsigned char>(PIN_START + i);
  //QTRSensorsRC*
  qtrrc1 = new QTRSensorsRC(pins, NUM_SENSORS/2);
  qtrrc2 = new QTRSensorsRC(&pins[NUM_SENSORS/2], NUM_SENSORS/2);
  Serial.begin(9600);
}

void loop() {
  qtrrc1->read(values);
  qtrrc2->read(&values[NUM_SENSORS/2]);
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
  delay(2000);
}
