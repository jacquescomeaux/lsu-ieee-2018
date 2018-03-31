#include "../include/SerialLink.h"

#include <libserialport.h>

#include "../include/Fixed.h"

#include <iostream>

int SerialLink::object_count = 0;
struct sp_port* SerialLink::port;

SerialLink::SerialLink() : PORTNAME("/dev/ttyACM0"), BAUD(9600) {
  object_count++;
  //std::cout << "Constructing object " << object_count << std::endl;
  if(object_count == 1) {
    //std::cout << "Initializing serial link " << object_count << std::endl;
    sp_get_port_by_name(PORTNAME, &port);
    sp_open(port, SP_MODE_READ_WRITE);	
    sp_set_baudrate(port, BAUD);
  }
}

SerialLink::~SerialLink() {
  //std::cout << "Destructing object " << object_count << std::endl;
  if(object_count == 1) {sp_close(port);
  //std::cout << "Freeing serial link " << object_count << std::endl;
  }
  object_count--;
}


char SerialLink::receiveChar() const {
  char c;
  receiveBuffer(&c, sizeof(char));
  std::cout << "Receiving " << c << std::endl;
  return c;
}

int SerialLink::receiveInt() const {
  int n;
  receiveBuffer(&n, sizeof(int));
  return n;
}

float SerialLink::receiveFloat() const {
  float x;
  receiveBuffer(&x, sizeof(float));
  return x;
}

void SerialLink::receiveBuffer(void* buf, size_t size) const {
  sp_blocking_read(port, buf, size, 0);
}

void SerialLink::transmitChar(char c) const {
  std::cout << "Writing " << c << std::endl;
  transmitBuffer(&c, sizeof(char));
}

void SerialLink::transmitIndex(unsigned int n) const {
  uint16_t twobytes = static_cast<uint16_t>(n);
  transmitBuffer(&twobytes, sizeof(uint16_t));
}

void SerialLink::transmitDirection(Direction d) const {
  uint8_t i = static_cast<uint8_t>(d);
  int out = static_cast<int>(i);
  transmitBuffer(&i, sizeof(uint8_t));
  std::cout << "Writing Direction " << out << std::endl;
}

void SerialLink::transmitValue(int n) const {
  Fixed f = n;
  uint64_t i = f.getInternal();
  transmitBuffer(&i, sizeof(uint64_t));
}

void SerialLink::transmitValue(float x) const {
  Fixed f = static_cast<double>(x);
  uint64_t i = f.getInternal();
  transmitBuffer(&i, sizeof(uint64_t));
}

void SerialLink::transmitBuffer(void* buf, size_t size) const {
  sp_blocking_write(port, buf, size, 0);
}
