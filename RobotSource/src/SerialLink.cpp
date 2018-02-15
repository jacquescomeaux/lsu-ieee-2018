#include "../include/SerialLink.h"
#include <libserialport.h>

SerialLink::SerialLink() : PORTNUM(24), BAUD(9600), CONFIG("8N1") {
  struct sp_port* port;
  get_port_by_name("/dev/ACM0", &port);
  sp_open(port, enum sp_mode flags);	
  sp_set_baudrate(port, 9600);
}

SerialLink::~SerialLink() {
  struct sp_port* port;
  get_port_by_name("/dev/ACM0", &port);
  sp_close(port, enum sp_mode flags);	
  sp_set_baudrate(port, 9600);
}

int SerialLink::receiveInt() const {
  union multinum n;
  //int bytes_received = 0;
  SerialLink::receiveBuffer(n.data, sizeof(int));
  //while(bytes_received != sizeof(int)) bytes_received += RS232_PollComport(PORTNUM, n.data + bytes_received, sizeof(int) - bytes_received);
  return n.integer;
}

float SerialLink::receiveFloat() const {
  union multinum n;
  SerialLink::receiveBuffer(n.data, sizeof(float));
  //float bytes_received = 0;
  //while(bytes_received != sizeof(float)) bytes_received += RS232_PollComport(PORTNUM, n.data + bytes_received, sizeof(float) - bytes_received);
  return n.floating;
}

void SerialLink::transmitInt(int n) const {
  //union multinum n;
  //n.integer = t;
  //RS232_SendBuf(PORTNUM, n.data, sizeof(int));
  SerialLink::transmitBuffer(&n, sizeof(int));
}

void SerialLink::transmitFloat(float n) const {
  //union multinum n;
  //n.floating = t;
  //RS232_SendBuf(PORTNUM, n.data, sizeof(float));
  SerialLink::transmitBuffer(&n, sizeof(float));
}

void SerialLink::receiveBuffer(void* buf, int size) const {
  int bytes_received = 0;
  while(bytes_received != size) RS232_PollComport(PORTNUM, static_cast<unsigned char*>(buf) + bytes_received, size - bytes_received);
}

void SerialLink::transmitBuffer(void* buf, int size) const {
  RS232_SendBuf(PORTNUM, static_cast<unsigned char*>(buf), size);
}
