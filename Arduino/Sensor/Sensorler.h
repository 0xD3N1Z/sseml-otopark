#ifndef SENSORLER_H
#define SENSORLER_H

#include <Arduino.h>

struct ParkAlanlari {
  int A1 = -1;
  int A2 = -1;
  int A3 = -1;
  int A4 = -1;
  int A5 = -1;
  int A6 = -1;
  int A7 = -1;
  int A8 = -1;
  int A9 = -1;
  int A10 = -1;
  int A11 = -1;
  int A12 = -1;
  int A13 = -1;
  int A14 = -1;

  int B1 = -1;
  int B2 = -1;
  int B3 = -1;
  int B4 = -1;
  int B5 = -1;
  int B6 = -1;
  int B7 = -1;
  int B8 = -1;
  int B9 = -1;
  int B10 = -1;
  int B11 = -1;
  int B12 = -1;
  int B13 = -1;
  int B14 = -1;
}

struct HavaDurumu {
  int sicaklik = -1;
  int nem = -1;
  int basinc = -1;
  int voc = -1;
}




class OtoparkSensorler {
public:

  void init();

  void hallet();
};

#endif