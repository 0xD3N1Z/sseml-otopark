#ifndef PARKEKRAN_H
#define PARKEKRAN_H

#include "ParkSensorler.h"

class ParkEkran {
 public:
    void init();

    void handle(SensorDurumu &sensorDurum);

  private:
    unsigned long _prevPageSwitchMillis = 0;
    int _currentPageIndex = 0;

    void sseml();

    void doluluk(SensorDurumu &sensorDurum);

    void saat_hava_durumu(SensorDurumu &sensorDurum);

    void guc_bilgisi(SensorDurumu &sensorDurum);

    void rfid();
};

#endif