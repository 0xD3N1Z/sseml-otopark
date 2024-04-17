#ifndef LED_H
#define LED_H

#include <Arduino.h>

class ParkLed {
 public:
    void init();

    void handle();
};

#endif