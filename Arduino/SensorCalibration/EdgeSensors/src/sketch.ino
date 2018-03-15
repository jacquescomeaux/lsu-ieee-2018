// defines pins numbers
const int trigPin = 5;
const int echoPin = 6;


// defines variables
long duration;
int distance_cm;
int distance_mm;
int distance_smaller;
int distanceInch;

void setup() {
pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
pinMode(echoPin, INPUT); // Sets the echoPin as an Input
Serial.begin(9600); // Starts the serial communication
}

void loop() {
  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance_cm = duration*0.034/2;
  distance_mm = (duration*0.034/2) * 10;
  distance_smaller = (duration*0.034/2) * 200;
  distanceInch = duration*0.0133/2;
  
  // Prints the distance on the Serial Monitor
  Serial.print("Distance: ");
  Serial.print(distance_smaller);
  Serial.print(" small, ");
  Serial.print(distance_mm);
  Serial.print(" mm, ");
  Serial.print(distance_cm);
  Serial.print(" cm, ");
  Serial.print(distanceInch);
  Serial.println(" in");
}
