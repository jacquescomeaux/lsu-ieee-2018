#include <cstdlib>
#include <iostream>
#include "rs232.h"

const int PORTNUM = 24;

union intchar {
  int number;
  unsigned char data[4];
};

int receiveInt() {
  union intchar n;
  int bytes_received = 0;
  while(bytes_received != 4) bytes_received += RS232_PollComport(PORTNUM, n.data + bytes_received, sizeof(int) - bytes_received);
  return n.number;
}

void transmitInt(int t) {
  union intchar n;
  n.number = t;
  RS232_SendBuf(PORTNUM, n.data, sizeof(int));
}

int main() {

  RS232_OpenComport(PORTNUM, 9600, "8N1");
  
  int number;
  std::cout << "enter number: ";
  std::cin >> number;
  
  while(number) {
    RS232_flushRXTX(PORTNUM);
    transmitInt(number);
    number = receiveInt();
    std::cout << "result: " << number << std::endl << "enter number: ";
    std::cin >> number;
  } 
  
  RS232_CloseComport(PORTNUM);

  return 0;
}
