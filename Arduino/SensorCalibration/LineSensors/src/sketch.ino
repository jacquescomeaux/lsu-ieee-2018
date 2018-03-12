#include <QTRSensors.h>

const int NUM_SENSORS = 32;
const unsigned char PIN_START = 22;
QTRSensorsRC qtrrc1, qtrrc2;
unsigned int values1[NUM_SENSORS/2];
unsigned int values2[NUM_SENSORS/2];
unsigned char pins1[NUM_SENSORS/2];
unsigned char pins2[NUM_SENSORS/2];

/*
QTRSensorsRC qtrrc;
unsigned char pins[1] = {53};
unsigned char pinsR[5] = {52, 53, 22, 23, 24};
unsigned char pinsF[5] = {28, 29, 30, 31, 32};
unsigned char pinsL[5] = {36, 37, 38, 39, 40};
unsigned char pinsB[5] = {44, 45, 46, 47, 48};
unsigned int values[1];
*/
void setup() {
  //for(int i = 22; i < 54; i++) pinMode(i, INPUT);
  for(unsigned char i = 0; i < NUM_SENSORS/2; i++) pins1[i] = static_cast<unsigned char>(PIN_START + i);
  for(unsigned char i = 0; i < NUM_SENSORS/2; i++) pins2[i] = static_cast<unsigned char>(PIN_START + NUM_SENSORS/2 + i);
  qtrrc1 = QTRSensorsRC(pins1, NUM_SENSORS/2);
  qtrrc2 = QTRSensorsRC(pins2, NUM_SENSORS/2);
  
  //qtrrc = QTRSensorsRC(pinsR, 5);
  //qtrrc = QTRSensorsRC(pins, 1);
  Serial.begin(9600);
}

void loop() {
  qtrrc1.read(values1);
  qtrrc2.read(values2);
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
  /*qtrrc.read(values);
  for(int i = 0; i < 1; i++) {
    Serial.print("S");
    Serial.print(i);
    Serial.print(": ");
    Serial.print("p");
    Serial.print(pins[i]);
    unsigned int v = values[i];
    Serial.print(" v: ");
    if(v < 1000) Serial.print(" "); 
    if(v < 100) Serial.print(" "); 
    if(v < 10) Serial.print(" "); 
    Serial.print(values[i]);
    Serial.print("   ");
  }*/
  Serial.println("\n------------------------------------------------------------------------------------------------");
  delay(2000);
}
