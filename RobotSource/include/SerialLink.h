#ifndef SERIALLINK_H
#define SERIALLINK_H

#include <libserialport.h>

class SerialLink {
  protected:
    SerialLink();
    const char* PORT, CONFIG;
    const int BAUD;
    struct sp_port* port;
    int receiveInt() const;
    float receiveFloat() const;
    void transmitInt(int) const;
    void transmitFloat(float) const;
    void receiveBuffer(void*, int) const;
    void transmitBuffer(void*, int) const;
    union multinum {
      float floating;
      int integer;
      unsigned char data[4];
    };
};

#endif
