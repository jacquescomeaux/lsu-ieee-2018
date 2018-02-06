#include "SerialLink.h"
#include "rs232.h"

SerialLink::SerialLink() : PORTNUM(24), BAUD(9600), THING("8N1"){
  RS232_OpenComport(PORTNUM, 9600, "8N1");
}

SerialLink::~SerialLink() : PORTNUM(24) {
  RS232_CloseComport(PORTNUM);
}

int SerialLink::receiveNumber() const {
  return 0;
}

float SerialLink::receiveNumber() const {
  union intchar n;
  int bytes_received = 0;
  while(bytes_received != 4) bytes_received += RS232_PollComport(PORTNUM, n.data + bytes_received, sizeof(int) - bytes_received);
  return n.number;
  return 0;
}

void SerialLink::transmitNumber(int) const {
  union intchar n;
  n.number = t;
  RS232_SendBuf(PORTNUM, n.data, sizeof(int));
  return;
}

void SerialLink::transmitNumber(float) const {
  return;
}
