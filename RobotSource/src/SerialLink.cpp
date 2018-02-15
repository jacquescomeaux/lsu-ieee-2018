#include "../include/SerialLink.h"

SerialLink::SerialLink() : PORTNAME("/dev/ttyACM0"), BAUD(9600) {//, CONFIG("8N1") {
  sp_get_port_by_name(PORTNAME, &port);
  sp_open(port, SP_MODE_READ_WRITE);	
  sp_set_baudrate(port, BAUD);
}

SerialLink::~SerialLink() {
  sp_close(port);	
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

void SerialLink::receiveBuffer(void* buf, size_t size) const {
  sp_blocking_read(this->port, buf, size, 0);
}

void SerialLink::transmitBuffer(void* buf, size_t size) const {
  sp_nonblocking_write(this->port, buf, size);
}
