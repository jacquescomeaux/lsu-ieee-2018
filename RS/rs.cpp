#include <cstdlib>
#include <iostream>
//#include "rs232.h"
#include <libserialport.h>

struct sp_port* port;

union intchar {
  int number;
  unsigned char data[4];
};

int receiveInt() {
  //union intchar n;
  //int bytes_received = 0;
  //while(bytes_received != 4) bytes_received += RS232_PollComport(PORTNUM, n.data + bytes_received, sizeof(int) - bytes_received);
  int n;
  sp_blocking_read(port, &n, 4, 0);
  //return n.number;
  return n;
}

void transmitInt(int t) {
  //union intchar n;
  //n.number = t;
  //RS232_SendBuf(PORTNUM, n.data, sizeof(int));
  sp_nonblocking_write(port, &t, 4);//, 0);
  //return n.number;
  //return n;
}

int main() {
  
  sp_get_port_by_name("/dev/ttyACM0", &port);
  sp_open(port, SP_MODE_READ_WRITE);	
  sp_set_baudrate(port, 9600);
  
  int number;
  std::cout << "enter number: ";
  std::cin >> number;
  
  while(number) {
    //RS232_flushRXTX(PORTNUM);
    transmitInt(number);
    number = receiveInt();
    std::cout << "result: " << number << std::endl << "enter number: ";
    std::cin >> number;
  } 
  
  sp_close(port);	

  return 0;
}
