#include <QTRSensors.h>

int LED = 13;
#define NUM_SENSORS             6  // number of sensors used
#define NUM_SAMPLES_PER_SENSOR  4000  // average 4 analog samples per sensor reading
#define EMITTER_PIN             2  // emitter is controlled by digital pin 2

// sensors 0 are connected to analog inputs 0 through 5, respectively
QTRSensorsRC qtra((unsigned char[]) {30, 31, 32, 33, 34, 35}, 
  NUM_SENSORS, NUM_SAMPLES_PER_SENSOR, QTR_NO_EMITTER_PIN);
unsigned int sensorValues[NUM_SENSORS];


void setup()
{
  Serial.begin(9600); // set the data rate in bits per second for serial data transmission
  delay(1000);
  pinMode(LED, OUTPUT);
}


void loop()
{
  // read raw sensor values
  qtra.read(sensorValues);
    Serial.print("Sensor 30: ");
    Serial.print(sensorValues[0]);
    Serial.print("  Sensor 31: ");
    Serial.print(sensorValues[1]);
    Serial.print("  Sensor 32: ");
    Serial.print(sensorValues[2]);

    Serial.print(" Sensor 33: ");
    Serial.print(sensorValues[3]);
    Serial.print("  Sensor 34: ");
    Serial.print(sensorValues[4]);
    Serial.print("  Sensor 35: ");
    Serial.print(sensorValues[5]);
    Serial.println();
    delay(500);
    
   

    if (sensorValues[0] < 2000 && sensorValues[1] < 2000 && sensorValues[2] < 2000){
      digitalWrite(LED, HIGH);}
    else{
      digitalWrite(LED, LOW);
    }
   
}
