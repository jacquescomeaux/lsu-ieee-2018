#include <Adafruit_MotorShield.h>
#include <MagnetArm.h>

<<<<<<< HEAD
  MagnetArm* test_arm;
  //Adafruit_StepperMotor* test_arm;

void setup() {
  Adafruit_MotorShield AFMS(0x61);
  test_arm = new MagnetArm(AFMS.getStepper(200, 2));
  //test_arm = AFMS.getStepper(200, 2);
  AFMS.begin();
  //test_arm->setSpeed(30);
=======
MagnetArm* test_arm;

void setup() {
  Adafruit_MotorShield AFMS(0x61);
  Adafruit_MotorShield AFMS2(0x60);
  AFMS.begin();
  AFMS2.begin();
  test_arm = new MagnetArm(AFMS.getStepper(200, 2), AFMS2.getMotor(1));
>>>>>>> 05086b85c6342e73b17576471d0debdc8edd7099
  Serial.begin(9600);
  Serial.write("Magnet Arm Ready");
}

void parseCommand(char c) {
  switch(c) {
    case 'r':
      Serial.println("Resetting arm"); 
      test_arm->reset();
<<<<<<< HEAD
      //test_arm->step(100, FORWARD, SINGLE);
      //test_arm->release();
=======
>>>>>>> 05086b85c6342e73b17576471d0debdc8edd7099
      break;
    case 'p':
      Serial.println("Picking up token"); 
      test_arm->pickUpToken();
<<<<<<< HEAD
      //test_arm->step(100, BACKWARD, SINGLE);
      //test_arm->release();
=======
>>>>>>> 05086b85c6342e73b17576471d0debdc8edd7099
      break;
    case 's':
      Serial.println("Storing Token"); 
      test_arm->storeToken();
<<<<<<< HEAD
      //test_arm->step(10, BACKWARD, SINGLE);
      //test_arm->release();
      break;
    /*case 'w':
      Serial.println("Storing Token"); 
      //test_arm->storeToken();
      test_arm->step(10, FORWARD, SINGLE);
      test_arm->release();
=======
>>>>>>> 05086b85c6342e73b17576471d0debdc8edd7099
      break;
    */default:
      break; 
  }
}

void loop() {
  if(Serial.available()) parseCommand(Serial.read());
}
