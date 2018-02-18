#ifndef SERIALLINK_H
#define SERIALLINK_H

class SerialLink {
  protected:
    SerialLink();
    ~SerialLink();
    const char* CONFIG;
    const int PORTNUM, BAUD;
    int receiveInt() const;
    float receiveFloat() const;
    void transmitChar(char) const;
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
