#include <Adafruit_MotorShield.h>
#include <SortingSystem.h>

SortingSystem* sorter;

void parseCommand(char c) {
  switch(c) {
    case 'p':
      Serial.println("Picking up token"); 
      sorter->pickUpToken();
      break;
    case 'R':
      Serial.println("Storing Token"); 
      sorter->storeToken(Color::RED);
      break;
    case 'G':
      Serial.println("Storing Token"); 
      sorter->storeToken(Color::GREEN);
      break;
    case 'B':
      Serial.println("Storing Token"); 
      sorter->storeToken(Color::BLUE);
      break;
    case 'C':
      Serial.println("Storing Token"); 
      sorter->storeToken(Color::CYAN);
      break;
    case 'M':
      Serial.println("Storing Token"); 
      sorter->storeToken(Color::MAGENTA);
      break;
    case 'Y':
      Serial.println("Storing Token"); 
      sorter->storeToken(Color::YELLOW);
      break;
    case 'K':
      Serial.println("Storing Token"); 
      sorter->storeToken(Color::GRAY);
      break;
    case 'd':
      Serial.println("Resetting arm"); 
      sorter->dropNextTokenStack();
      break;
    default:
      break; 
  }
}

void setup() {
  Adafruit_MotorShield AFMS[3];
  for(int i = 0; i < 3; i++) AFMS[i] = Adafruit_MotorShield(0x60 + i);
  for(auto& m : AFMS) m.begin();
  sorter = new SortingSystem(AFMS[1].getStepper(200, 2), AFMS[0].getMotor(1), AFMS[2].getStepper(200, 2));
  Serial.begin(9600);
  Serial.write("Magnet Arm Ready");
}

void loop() {
  while(true) {
    if(Serial.available()) parseCommand(Serial.read());
    sorter->continueSorting();
  }
}
