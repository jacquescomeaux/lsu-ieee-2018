#include "../include/SerialLink.h"

#include <libserialport.h>

#include "../include/Fixed.h"

#include <iostream>
#include <iomanip>

int SerialLink::object_count = 0;
struct sp_port* SerialLink::port;

SerialLink::SerialLink() : PORTNAME("/dev/ttyACM0"), BAUD(115200) {
  object_count++;
  if(object_count == 1) {
    sp_get_port_by_name(PORTNAME, &port);
    sp_open(port, SP_MODE_READ_WRITE);	
    sp_set_baudrate(port, BAUD);
  }
}

SerialLink::~SerialLink() {
  if(object_count == 1) sp_close(port);
  object_count--;
}


char SerialLink::receiveChar() const {
  char c;
  receiveBuffer(&c, sizeof(char));
  //std::cout << "Receiving " << c << std::endl;
  return c;
}

void SerialLink::waitForChar(char c) {
  if(response_buffer.find(c) != response_buffer.end()) response_buffer.erase(response_buffer.find(c));
  else for(char r = receiveChar(); r != c; r = receiveChar()) response_buffer.insert(r);
}

int SerialLink::receiveInt() const {
  int n;
  receiveBuffer(&n, sizeof(int));
  return n;
}

double SerialLink::receiveFloat() const {
  double x;
  receiveBuffer(&x, sizeof(double));
  return x;
}

void SerialLink::receiveBuffer(void* buf, size_t size) const {
  sp_blocking_read(port, buf, size, 0);
}

void SerialLink::transmitChar(char c) const {
  //std::cout << "Writing " << c << std::endl;
  transmitBuffer(&c, sizeof(char));
}

void SerialLink::transmitIndex(unsigned int n) const {
  //std::cout << "sending index" << n << std::endl;
  uint16_t twobytes = static_cast<uint16_t>(n);
  transmitBuffer(&twobytes, sizeof(uint16_t));
}

void SerialLink::transmitVelocityVector(VelocityVector v) const {
  //uint8_t i = static_cast<uint8_t>(d);
  //int out = static_cast<int>(i);
  transmitValue(v.x);
  transmitValue(v.y);
  transmitValue(v.rot);
  //transmitBuffer(&i, sizeof(uint8_t));
  //std::cout << "Writing Direction " << out << std::endl;
}

void SerialLink::transmitColor(Color c) const {
  uint8_t i = static_cast<uint8_t>(c);
  int out = static_cast<int>(i);
  transmitBuffer(&i, sizeof(uint8_t));
  //std::cout << "Writing Color " << out << std::endl;
}

void SerialLink::transmitBool(bool b) const {
  transmitIndex(b ? 1 : 0);
}

void SerialLink::transmitValue(int n) const {
  Fixed f = n;
  //std::cout << "transmiting fixed "<< f.getInt() << std::endl;
  int64_t i = f.getInternal();
  transmitBuffer(&i, sizeof(int64_t));
}

void SerialLink::transmitValue(double x) const {
  Fixed f = static_cast<double>(x);
  //std::cout << "transmiting fixed "<< f.getDouble() << std::endl;
  int64_t i = f.getInternal();
  transmitBuffer(&i, sizeof(int64_t));
}

void SerialLink::transmitBuffer(void* buf, size_t size) const {
  //std::cout << "transmitting buffer of size " << size << std::endl;
  //for(size_t s = 0; s < size; s++) std::cout << std::hex << std::setfill('0') << std::setw(2) << static_cast<int>(static_cast<unsigned char*>(buf)[s]) << " ";
  //std::cout << std::endl;
  sp_blocking_write(port, buf, size, 0);
}
