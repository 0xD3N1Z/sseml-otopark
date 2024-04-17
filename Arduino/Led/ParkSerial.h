#ifndef PARKSERIAL_H
#define PARKSERIAL_H

#include "ParkLed.h"

class ParkSerial {
  public:
    void init();

    void handle(ParkDurumu &pDurumu);

  private:
    String _serialcmd;
    String _crcstr;
};

#endif