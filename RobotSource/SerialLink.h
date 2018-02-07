#ifndef SERIALLINK_H
#define SERIALLINK_H

class SerialLink {
  protected:
    SerialLink();
    ~SerialLink();
    const string CONFIG:
    const int PORTNUM, BAUD;
    int receiveNumber() const;
    float receiveNumber() const;
    void transmitNumber(int) const;
    void transmitNumber(float) const;
};

#endif
