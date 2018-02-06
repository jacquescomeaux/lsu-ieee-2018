#ifndef SERIALLINK_H
#define SERIALLINK_H

class SerialLink {
  protected:
    SerialLink();
    ~SerialLink();
    const int PORTNUM;
    int receiveNumber() const;
    float receiveNumber() const;
    void transmitNumber(int) const;
    void transmitNumber(float) const;
};

#endif
