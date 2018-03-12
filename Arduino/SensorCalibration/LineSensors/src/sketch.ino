#include <QTRSensors.h>

const int NUM_SENSORS = 32;
const unsigned char PIN_START = 22;
QTRSensorsRC* qtrrc1, qtrrc2;
unsigned int values1[NUM_SENSORS/2];
unsigned int values2[NUM_SENSORS/2];
unsigned char pins1[NUM_SENSORS/2];
unsigned char pins2[NUM_SENSORS/2];

void setup() {
  for(unsigned char i = 0; i < NUM_SENSORS/2; i++) pins1[i] = static_cast<unsigned char>(PIN_START + i);
  for(unsigned char i = 0; i < NUM_SENSORS/2; i++) pins2[i] = static_cast<unsigned char>(PIN_START + NUM_SENSORS/2 + i);
  qtrrc1 = new QTRSensorsRC(pins1, NUM_SENSORS/2);
  qtrrc2 = new QTRSensorsRC(pins2, NUM_SENSORS/2);
 Serial.begin(9600);
}

void loop() {
  qtrrc1->read(values1);
  qtrrc2->read(values2);
  for(int i = 0; i < 4; i++) {
    for(int j = 0; j < 8; j++) {
      int k = i*8+j;
      Serial.print("S");
      if(k<10) Serial.print("0");
      Serial.print(k);
      Serial.print(": p");
      Serial.print((k<16) ? pins1[k] : pins2[k-16]);
      unsigned int v = (k<16) ? values1[k] : values2[k-16];
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
