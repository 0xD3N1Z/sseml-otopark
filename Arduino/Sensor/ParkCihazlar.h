#ifndef PARKCIHAZLAR_H
#define PARKCIHAZLAR_H

#include "ParkSensorler.h"
#include <RtcDS1302.h>

struct CihazDurumu {
  RtcDateTime rtc_date;

  bool giris_servo = false;
  bool cikis_servo = false;

  bool giris_bekleme = false;
  bool cikis_bekleme = false;
};

class ParkCihazlar {
 public:
    void init();

    void handle(SensorDurumu &sensorDurum, CihazDurumu &cihazDurum);

  private:
    unsigned long _prevServoMillis = 0;
    unsigned long _prevServoWaitMillis = 0;
    unsigned long _prevRtcMillis = 0;

    void servo(SensorDurumu &sensorDurum, CihazDurumu &cihazDurum);

    void rtc(CihazDurumu &cihazDurum);
};

#endif