#include "SerialLink.h"
#include "rs232.h"

SerialLink::SerialLink() : PORTNUM(24), BAUD(9600), CONFIG("8N1") {
  RS232_OpenComport(PORTNUM, BAUD, CONFIG);
}

SerialLink::~SerialLink() {
  RS232_CloseComport(PORTNUM);
}

int SerialLink::receiveNumber() const {
  union multinum n;
  //int bytes_received = 0;
  SerialLink::receiveBuffer(n.data, sizeof(int));
  //while(bytes_received != sizeof(int)) bytes_received += RS232_PollComport(PORTNUM, n.data + bytes_received, sizeof(int) - bytes_received);
  return n.integer;
}

float SerialLink::receiveNumber() const {
  union multinum n;
  SerialLink::receiveBuffer(n.data, sizeof(float));
  //float bytes_received = 0;
  //while(bytes_received != sizeof(float)) bytes_received += RS232_PollComport(PORTNUM, n.data + bytes_received, sizeof(float) - bytes_received);
  return n.floating;
}

void SerialLink::transmitNumber(int n) const {
  //union multinum n;
  //n.integer = t;
  //RS232_SendBuf(PORTNUM, n.data, sizeof(int));
  SerialLink::transmitBuffer(&n, sizeof(int));
}

void SerialLink::transmitNumber(float) const {
  //union multinum n;
  //n.floating = t;
  //RS232_SendBuf(PORTNUM, n.data, sizeof(float));
  SerialLink::transmitBuffer(&n, sizeof(float));
}

void receiveBuffer(void* buf, int size) const {
  int bytes_received = 0;
  while(bytes_received != size) RS232_PollComport(PORTNUM, buf + bytes_received, size - bytes_received);
}

void transmitBuffer(void* buf, int size) const {
  RS232_SendBuf(PORTNUM, buf, size);
}
