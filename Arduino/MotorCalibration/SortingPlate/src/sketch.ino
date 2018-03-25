#include <Adafruit_MotorShield.h>
#include <SortingPlate.h>

SortingPlate* test_plate;
bool paused;

void setup() {
  Adafruit_MotorShield AFMS(0x62);
  AFMS.begin();
  test_plate = new SortingPlate(AFMS.getStepper(200, 2));
  Serial.begin(9600);
  Serial.println("Sorting Plate Ready");
  paused = true;
}

void parseCommand(char c) {
  String s;
  switch(c) {
    case 'p':
      Serial.println(test_plate->ready()?"Ready":"Not ready");
      break;
    case 'r':
      Serial.println("Resetting plate"); 
      test_plate->reset();
      break;
    case 'j':
      while(!Serial.available());
      c = Serial.read();
      s = c;
      Serial.println("Rotating CCW"); 
      test_plate->rotateCCW(static_cast<unsigned int>(s.toInt()));
      break;
    case 'k':
      Serial.println("Rotating CW"); 
      test_plate->rotateCW();
      break;
    case ' ':
      paused = !paused;
      Serial.println(paused?"Paused":"Resumed");
      break; 
    default:
      break; 
  }
}

void loop() {
  if(Serial.available()) parseCommand(Serial.read());
  if(!paused) test_plate->continueMoving();
}
