#include "../include/SerialLink.h"

#include <libserialport.h>

#include <iostream>

int SerialLink::object_count = 0;
struct sp_port* SerialLink::port;

SerialLink::SerialLink() : PORTNAME("/dev/ttyACM0"), BAUD(9600) {
  object_count++;
  std::cout << "Constructing object " << object_count << std::endl;
  if(object_count == 1) {
    std::cout << "Initializing serial link " << object_count << std::endl;
    sp_get_port_by_name(PORTNAME, &port);
    sp_open(port, SP_MODE_READ_WRITE);	
    sp_set_baudrate(port, BAUD);
  }
}

SerialLink::~SerialLink() {
  std::cout << "Destructing object " << object_count << std::endl;
  if(object_count == 1) {sp_close(port); std::cout << "Freeing serial link " << object_count << std::endl;}
  object_count--;
}

int SerialLink::receiveInt() const {
  int n;
  receiveBuffer(&n, sizeof(int));
  return n;
}

float SerialLink::receiveFloat() const {
  float n;
  receiveBuffer(&n, sizeof(float));
  return n;
}

void SerialLink::transmitChar(char c) const {
  transmitBuffer(&c, sizeof(char));
}

void SerialLink::transmitInt(int n) const {
  transmitBuffer(&n, sizeof(int));
}

void SerialLink::transmitFloat(float n) const {
  transmitBuffer(&n, sizeof(float));
}

void SerialLink::receiveBuffer(void* buf, size_t size) const {
  sp_blocking_read(port, buf, size, 0);
}

void SerialLink::transmitBuffer(void* buf, size_t size) const {
  sp_nonblocking_write(port, buf, size);
}
