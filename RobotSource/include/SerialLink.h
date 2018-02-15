#ifndef SERIALLINK_H
#define SERIALLINK_H

#include <libserialport.h>

class SerialLink {
  protected:
    SerialLink();
    ~SerialLink();
    const char* PORTNAME;//, CONFIG;
    const int BAUD;
    struct sp_port* port;
    int receiveInt() const;
    float receiveFloat() const;
    void transmitInt(int) const;
    void transmitFloat(float) const;
    void receiveBuffer(void*, size_t) const;
    void transmitBuffer(void*, size_t) const;
    union multinum {
      float floating;
      int integer;
      unsigned char data[4];
    };
};

#endif
