#include "BufferToggle.h"
#include <iostream>
#include "rs232.h"

const int PORTNUM = 24;

int main() {
  BufferToggle bt;
  bt.off();
  RS232_OpenComport(PORTNUM, 9600, "8N1");
  char ch = '\0';
  std::cout << "Press q to quit\n";
  while((std::cin.get() >> ch) != 'q') std::cerr << ch;//RS232_SendByte(PORTNUM, ch);
  bt.on(); 
  RS232_CloseComport(PORTNUM);
  return 0;
}
