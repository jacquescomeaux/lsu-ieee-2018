#include <QTRSensors.h>

void setup() {
  unsigned char pinR[5] = {52, 53, 22, 23, 24};
  unsigned char pinF[5] = {28, 29, 30, 31, 32};
  unsigned char pinL[5] = {36, 37, 38, 39, 40};
  unsigned char pinB[5] = {44, 45, 46, 47, 48};
  QTRSensorsRC right(pinR, 5);
  QTRSensorsRC front(pinF, 5);
  QTRSensorsRC left(pinL, 5);
  QTRSensorsRC back(pinB, 5);
  unsigned int valuesR[5];
  unsigned int valuesF[5];
  unsigned int valuesL[5];
  unsigned int valuesB[5];
  Serial.begin(9600);
  while(true) {
    right.read(valuesR);
    front.read(valuesF);
    left.read(valuesL);
    back.read(valuesB);
    Serial.println("\nRight:");
    for(int i = 0; i < 5; i++) {Serial.print(valuesR[i]); Serial.println(" ");}
    Serial.println("\nFront:");
    for(int i = 0; i < 5; i++) {Serial.print(valuesF[i]); Serial.println(" ");}
    Serial.println("\nLeft:");
    for(int i = 0; i < 5; i++) {Serial.print(valuesL[i]); Serial.println(" ");}
    Serial.println("\nBack:");
    for(int i = 0; i < 5; i++) {Serial.print(valuesB[i]); Serial.println(" ");}
    delay(500);
  }
}

void loop() {}
