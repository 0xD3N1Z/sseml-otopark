#ifndef PARKSENSORLER_H
#define PARKSENSORLER_H

struct SensorDurumu {
  int tcrt5000A[14] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  int tcrt5000B[14] = {0, 0, 0, 0, 0, 0, 0, 0, 0 ,0, 0, 0, 0, 0};
};

class ParkSensorler {
 public:
    void init();

    void handle(SensorDurumu &sensorDurum);

  private:
    unsigned long _tcrtPrevMeasureMillis = 0;
    int _tcrt5000A_sampleCount[14] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    int _tcrt5000B_sampleCount[14] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

    const char* _muxTable[14] = {"0000", "1000", "0100", "1100", "0010", "1010", "0110", "1110", "0001", "1001", "0101", "1101", "0011", "1011"};

    void tcrt5000(SensorDurumu &sensorDurum);

    void mux(int sensor, char block);
};

#endif