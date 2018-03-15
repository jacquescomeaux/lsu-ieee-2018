#include <Adafruit_MotorShield.h>
#include <MagnetArm.h>

MagnetArm* test_arm;

void setup() {
  Adafruit_MotorShield AFMS(0x61);
  AFMS.begin();
  test_arm = new MagnetArm(AFMS.getStepper(200, 1));
  Serial.begin(9600);
  Serial.write("Magnet Arm Ready");
}

void parseCommand(char c) {
  switch(c) {
    case 'r':
      Serial.println("Resetting arm"); 
      test_arm->reset();
      break;
    case 'p':
      Serial.println("Picking up token"); 
      test_arm->pickUpToken();
      break;
    case 's':
      Serial.println("Storing Token"); 
      test_arm->storeToken();
      break;
    default:
      break; 
  }
}

void loop() {
  if(Serial.available()) parseCommand(Serial.read());
}
