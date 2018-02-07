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
    void receiveBuffer(void*, int) const;
    void transmitBuffer(void*, int) const;
    union multinum {
      float floating;
      int integer;
      unsigned char data[4];
    };
};

#endif
