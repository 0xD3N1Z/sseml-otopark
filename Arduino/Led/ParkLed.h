#ifndef PARKLED_H
#define PARKLED_H

struct ParkDurumu {
  int P1 = 0;
  int P2 = 0;
  int P3 = 0;
  int P4 = 0;
  int P5 = 0;
  int P6 = 0;
  int P7 = 0;
  int P8 = 0;
  int P9 = 0;
  int P10 = 0;
  int P11 = 0;
  int P12 = 0;
  int P13 = 0;
  int P14 = 0;
};

class ParkLed {
 public:
    void init();

    void handle();
};

#endif