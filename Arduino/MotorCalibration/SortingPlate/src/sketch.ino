#include <Adafruit_MotorShield.h>
#include <SortingPlate.h>

SortingPlate* test_plate;
bool paused;

void setup() {
  Adafruit_MotorShield AFMS(0x61);
  AFMS.begin();
  test_plate = new SortingPlate(AFMS.getStepper(200, 1));
  Serial.begin(9600);
  Serial.write("Sorting Plate Ready");
  paused = true;
}

void parseCommand(char c) {
  switch(c) {
    case 'p':
      Serial.println(test_plate->ready()?"Ready":"Not ready");
      break;
    case 'r':
      Serial.println("Resetting plate"); 
      test_plate->reset();
      break;
    case 'c':
      c = Serial.read();
      Serial.println("Rotating CW"); 
      test_plate->rotateCW(static_cast<int>(c));
      break;
    case 'x':
      Serial.println("Rotating CCW"); 
      test_plate->rotateCCW();
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
  test_plate->continueMoving();
}
