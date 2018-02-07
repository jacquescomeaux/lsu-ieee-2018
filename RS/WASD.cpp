<<<<<<< HEAD
=======
#include "BufferToggle.h"
>>>>>>> 565aa7f17a599692e95f159fc34535c5d90dd8ae
#include <iostream>
#include "rs232.h"

const int PORTNUM = 24;

int main() {
  RS232_OpenComport(PORTNUM, 9600, "8N1");
  unsigned char ch = '\0';
  std::cout << "Press q to quit\n";
  while(ch != 'q') {
    RS232_SendByte(PORTNUM, ch);
    std::cin >> ch;
  }
  RS232_CloseComport(PORTNUM);
  return 0;
}
