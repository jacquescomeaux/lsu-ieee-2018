#include <Adafruit_MotorShield.h>
#include <MagnetArm.h>

//MagnetArm* test_arm;
  Adafruit_StepperMotor* test_arm;

void setup() {
  Adafruit_MotorShield AFMS(0x61);
  AFMS.begin();
  Adafruit_StepperMotor* test_arm;
  //test_arm = new MagnetArm(AFMS.getStepper(200, 3));
  test_arm = AFMS.getStepper(200, 3);
  test_arm->setSpeed(60);
  Serial.begin(9600);
  Serial.write("Magnet Arm Ready");
}

void parseCommand(char c) {
  switch(c) {
    case 'r':
      Serial.println("Resetting arm"); 
      //test_arm->reset();
      test_arm->step(200, FORWARD, SINGLE);
      break;
    case 'p':
      Serial.println("Picking up token"); 
      //test_arm->pickUpToken();
      test_arm->step(200, BACKWARD, SINGLE);
      break;
    case 's':
      Serial.println("Storing Token"); 
      //test_arm->storeToken();
      break;
    default:
      break; 
  }
}

void loop() {
  if(Serial.available()) parseCommand(Serial.read());
}
