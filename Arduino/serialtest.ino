union int_thing {
  unsigned char bytes[4];
  char chars[4];
  uint32_t number;
};

int a; 

uint32_t endianize(uint32_t n) {
  union int_thing normal, reversed;
  normal.number = n;
  for(int i = 0; i < 4; i++) reversed.bytes[i] = normal.bytes[3-i];
  return reversed.number;
}

uint32_t receiveInt() {
  union int_thing r;
  //for(int i = 0; i < 4; i++) r.chars[i] = Serial.read();
  Serial.readBytes(r.chars, 4);
  return r.number;
}

void transmitInt(uint32_t transmit) {
  union int_thing t;
  t.number = transmit;
  //Serial.write(0xFF);
  Serial.write(t.bytes, 4);
  //Serial.flush();
}

void setup() {
  a = 0;
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
}

void loop() {
  if(Serial.available() >= 4) {
    if(++a%2) digitalWrite(LED_BUILTIN, HIGH);
    else digitalWrite(LED_BUILTIN, LOW);
    transmitInt(receiveInt() * 2);
  }
  //uint32_t x = 168496141;
  //transmitInt(x);
  //delay(300);
}
