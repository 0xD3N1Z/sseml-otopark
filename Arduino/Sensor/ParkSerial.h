#ifndef PARKSERIAL_H
#define PARKSERIAL_H

class ParkSerial {
  public:
    void init();

    void handle();

  private:
    String _serialcmd;
    String _crcstr;
};

#endif