#ifndef SERIALLINK_H
#define SERIALLINK_H

#include <libserialport.h>

#include "Direction.h"
#include "Color.h"

class SerialLink {
  private:
    static int object_count;
    static struct sp_port* port;
    const char* PORTNAME;
    const int BAUD;
  protected:
    SerialLink();
    ~SerialLink();
    char receiveChar() const;
    int receiveInt() const;
    float receiveFloat() const;
    void receiveBuffer(void*, size_t) const;
    void transmitChar(char) const;
    void transmitIndex(unsigned int) const;
    void transmitDirection(Direction) const;
    void transmitColor(Color) const;
    void transmitValue(int) const;
    void transmitValue(float) const;
    void transmitBuffer(void*, size_t) const;
};

#endif//SERIALLINK_H
