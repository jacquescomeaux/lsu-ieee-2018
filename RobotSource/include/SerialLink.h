#ifndef SERIALLINK_H
#define SERIALLINK_H

#include <libserialport.h>

class SerialLink {
  private:
    static int object_count;
    static struct sp_port* port;
    const char* PORTNAME;//, CONFIG;
    const int BAUD;
  protected:
    SerialLink();
    ~SerialLink();
    int receiveInt() const;
    float receiveFloat() const;
    void transmitChar(char) const;
    void transmitInt(int) const;
    void transmitFloat(float) const;
    void receiveBuffer(void*, size_t) const;
    void transmitBuffer(void*, size_t) const;
};

#endif//SERIALLINK_H
