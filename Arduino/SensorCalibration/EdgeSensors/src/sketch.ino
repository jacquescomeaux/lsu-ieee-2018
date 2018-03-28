// defines pins numbers
const int trigPins[4] = {6, 8, 10, 12};
const int echoPins[4] = {7, 9, 11, 14};

// defines variables
long duration;

void setup() {
  for(int i = 0; i < 4; i++) pinMode(trigPins[i], OUTPUT);
  for(int i = 0; i < 4; i++) pinMode(echoPins[i], INPUT);
  Serial.begin(9600);
}

void loop() {
  for(int i = 0; i < 4; i++) {
    digitalWrite(trigPins[i], LOW); // No output pulse initially.
    delayMicroseconds(2);
    digitalWrite(trigPins[i], HIGH); // Output pulse.
    delayMicroseconds(10);
    digitalWrite(trigPins[i], LOW);  // Disable output pulse.
    duration = pulseIn(echoPins[i], HIGH);  // Receive incoming pulse signal. 
    Serial.print("Sensor "); 
    Serial.print(i);
    Serial.print(": ");
    Serial.println(duration);
  }
  Serial.println();
  delay(1000);
}
