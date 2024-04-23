#ifndef PARKSENSORLER_H
#define PARKSENSORLER_H

struct SensorDurumu {
  int tcrt5000A[14] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  int tcrt5000B[14] = {0, 0, 0, 0, 0, 0, 0, 0, 0 ,0, 0, 0, 0, 0};

  int ldr[2] = {0, 0};

  float sicaklik = 0.0;
  float hissedilen_sicaklik = 0.0;
  float nem = 0.0;

  float dcCurrent = 0.0; //geç
  float solarVoltage = 0.0;
  float batteryVoltage = 0.0;
  bool solarInserted = false;
  bool wallPlugInserted = false;
};

class ParkSensorler {
 public:
    void init();

    void handle(SensorDurumu &sensorDurum);

  private:
    unsigned long _tcrtPrevMeasureMillis = 0;
    unsigned long _dhtPrevMeasureMillis = 0;
    unsigned long _ldrPrevMeasureMillis = 0;
    unsigned long _powerPrevMeasureMillis = 0;
    
    int _tcrt5000A_sampleCount[14] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    int _tcrt5000B_sampleCount[14] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

    const char* _muxTable[14] = {"0000", "1000", "0100", "1100", "0010", "1010", "0110", "1110", "0001", "1001", "0101", "1101", "0011", "1011"};

    int _ldr_sampleCount[2] = {0, 0};

    void tcrt5000(SensorDurumu &sensorDurum);

    void dht11(SensorDurumu &sensorDurum);

    void ldr(SensorDurumu &sensorDurum);

    void power(SensorDurumu &sensorDurum);

    void mux(int sensor, char block);
};

#endif