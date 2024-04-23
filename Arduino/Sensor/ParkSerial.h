#ifndef PARKSERIAL_H
#define PARKSERIAL_H

#include "ParkSensorler.h"
#include "ParkCihazlar.h"

class ParkSerial {
  public:
    void init();

    void handle(SensorDurumu &sensorDurum, CihazDurumu &cihazDurum);

  private:
    String _serialcmd;
    String _tcrt5000A_str;
    String _tcrt5000B_str;
    String _crc_a_str;
    String _crc_b_str;
};

#endif