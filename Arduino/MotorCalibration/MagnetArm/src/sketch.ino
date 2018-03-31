#include <Adafruit_MotorShield.h>
#include <MagnetArm.h>

  //MagnetArm* test_arm;
  Adafruit_StepperMotor* test_arm;

void setup() {
  Adafruit_MotorShield AFMS(0x62);
  //Adafruit_MotorShield AFMS2(0x60);
  test_arm = AFMS.getStepper(200, 1);
  AFMS.begin();
  //AFMS2.begin();
  //test_arm = new MagnetArm(AFMS.getStepper(200, 2), AFMS2.getMotor(1));
  
  test_arm->setSpeed(30);
  Serial.begin(9600);
  Serial.write("Magnet Arm Ready");
}

void parseCommand(char c) {
  switch(c) {
    case ',':
	Serial.println("Increment 5 Up");
	test_arm->step(5, FORWARD, DOUBLE);
	test_arm->release();
	break;
    case '.':
	Serial.println("Increment 5 Down");
	test_arm->step(5, BACKWARD, DOUBLE);
	test_arm->release();
	break;
    case 'r':
      Serial.println("Resetting arm"); 
      //test_arm->reset();
      //test_arm->step(100, FORWARD, SINGLE);
      //test_arm->release();
      break;
    case 'p':
      Serial.println("Picking up token"); 
      //test_arm->pickUpToken();
      //test_arm->step(100, BACKWARD, SINGLE);
      //test_arm->release();
      break;
    case 's':
      Serial.println("Storing Token"); 
      //test_arm->storeToken();
      //test_arm->step(10, BACKWARD, SINGLE);
      //test_arm->release();
      break;
    /*case 'w':
      Serial.println("Storing Token"); 
      //test_arm->storeToken();
      test_arm->step(10, FORWARD, SINGLE);
      test_arm->release();
      break;
    */default:
      break; 
  }
}

void loop() {
  if(Serial.available()) parseCommand(Serial.read());
}
