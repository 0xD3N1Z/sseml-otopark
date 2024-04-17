#include <Arduino.h> //Arduino kütüphanesi

#include "Led.h" //C++ header dosyası
#include "Config.h" //Ayarları içeren dosya

void ParkLed::init() {
  pinMode(LED_1, OUTPUT);
  pinMode(LED_2, OUTPUT);
  pinMode(LED_3, OUTPUT);
  pinMode(LED_4, OUTPUT);
  pinMode(LED_5, OUTPUT);
  pinMode(LED_6, OUTPUT);
  pinMode(LED_7, OUTPUT);
  pinMode(LED_8, OUTPUT);
  pinMode(LED_9, OUTPUT);
  pinMode(LED_10, OUTPUT);
  pinMode(LED_11, OUTPUT);
  pinMode(LED_12, OUTPUT);
  pinMode(LED_13, OUTPUT);
}

void ParkLed::handle() {
  
}