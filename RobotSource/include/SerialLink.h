#ifndef SERIALLINK_H
#define SERIALLINK_H

#include <libserialport.h>

#include "Color.h"

#include <set>

class SerialLink {
  private:
    static int object_count;
    static struct sp_port* port;
    const char* PORTNAME;
    const int BAUD;
    std::set<char> response_buffer;
  protected:
    SerialLink();
    ~SerialLink();
    char receiveChar() const;
    void waitForChar(char);
    int receiveInt() const;
    double receiveFloat() const;
    void receiveBuffer(void*, size_t) const;
    void transmitChar(char) const;
    void transmitIndex(unsigned int) const;
    void transmitVelocityVector(VelocityVector) const;
    void transmitColor(Color) const;
    void transmitBool(bool) const;
    void transmitValue(int) const;
    void transmitValue(double) const;
    void transmitBuffer(void*, size_t) const;
};

#endif//SERIALLINK_H
