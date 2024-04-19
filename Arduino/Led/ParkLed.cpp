#include <Arduino.h>  //Arduino kütüphanesi

#include "ParkLed.h"  //C++ header dosyası
#include "Config.h"   //Ayarları içeren dosya

//PUBLİC KODLAR

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

#ifdef LED_MASTER
  pinMode(LED_SYNC, OUTPUT);
#endif

#ifndef LED_MASTER
  pinMode(LED_SYNC, INPUT_PULLUP);
#endif
}

void ParkLed::handle(ParkDurumu &pDurumu) {
  off(pDurumu);    //Kapalı olması gereken park alanları (Boşta)
  on(pDurumu);     //Açık olması gereken park alanları (Dolu)
  blink(pDurumu);  //Yanıp sönmesi gereken park alanları (Öneriliyor)
}


//PRİVATE KODLAR

void ParkLed::off(ParkDurumu &pDurumu) {
  if (pDurumu.P1 == 0 && pDurumu.P2 == 0) digitalWrite(LED_1, LED_STATE_OFF);
  if (pDurumu.P2 == 0 && pDurumu.P3 == 0) digitalWrite(LED_2, LED_STATE_OFF);
  if (pDurumu.P3 == 0 && pDurumu.P4 == 0) digitalWrite(LED_3, LED_STATE_OFF);
  if (pDurumu.P4 == 0 && pDurumu.P5 == 0) digitalWrite(LED_4, LED_STATE_OFF);
  if (pDurumu.P5 == 0 && pDurumu.P6 == 0) digitalWrite(LED_5, LED_STATE_OFF);
  if (pDurumu.P6 == 0 && pDurumu.P7 == 0) digitalWrite(LED_6, LED_STATE_OFF);
  if (pDurumu.P7 == 0 && pDurumu.P8 == 0) digitalWrite(LED_7, LED_STATE_OFF);
  if (pDurumu.P8 == 0 && pDurumu.P9 == 0) digitalWrite(LED_8, LED_STATE_OFF);
  if (pDurumu.P9 == 0 && pDurumu.P10 == 0) digitalWrite(LED_9, LED_STATE_OFF);
  if (pDurumu.P10 == 0 && pDurumu.P11 == 0) digitalWrite(LED_10, LED_STATE_OFF);
  if (pDurumu.P11 == 0 && pDurumu.P12 == 0) digitalWrite(LED_11, LED_STATE_OFF);
  if (pDurumu.P12 == 0 && pDurumu.P13 == 0) digitalWrite(LED_12, LED_STATE_OFF);
  if (pDurumu.P13 == 0 && pDurumu.P14 == 0) digitalWrite(LED_13, LED_STATE_OFF);
}

void ParkLed::on(ParkDurumu &pDurumu) {
  if ((pDurumu.P1 == 1 || pDurumu.P2 == 1) && (pDurumu.P1 != 2 && pDurumu.P2 != 2)) digitalWrite(LED_1, LED_STATE_ON);
  if ((pDurumu.P2 == 1 || pDurumu.P3 == 1) && (pDurumu.P2 != 2 && pDurumu.P3 != 2)) digitalWrite(LED_2, LED_STATE_ON);
  if ((pDurumu.P3 == 1 || pDurumu.P4 == 1) && (pDurumu.P3 != 2 && pDurumu.P4 != 2)) digitalWrite(LED_3, LED_STATE_ON);
  if ((pDurumu.P4 == 1 || pDurumu.P5 == 1) && (pDurumu.P4 != 2 && pDurumu.P5 != 2)) digitalWrite(LED_4, LED_STATE_ON);
  if ((pDurumu.P5 == 1 || pDurumu.P6 == 1) && (pDurumu.P5 != 2 && pDurumu.P6 != 2)) digitalWrite(LED_5, LED_STATE_ON);
  if ((pDurumu.P6 == 1 || pDurumu.P7 == 1) && (pDurumu.P6 != 2 && pDurumu.P7 != 2)) digitalWrite(LED_6, LED_STATE_ON);
  if ((pDurumu.P7 == 1 || pDurumu.P8 == 1) && (pDurumu.P7 != 2 && pDurumu.P8 != 2)) digitalWrite(LED_7, LED_STATE_ON);
  if ((pDurumu.P8 == 1 || pDurumu.P9 == 1) && (pDurumu.P8 != 2 && pDurumu.P9 != 2)) digitalWrite(LED_8, LED_STATE_ON);
  if ((pDurumu.P9 == 1 || pDurumu.P10 == 1) && (pDurumu.P9 != 2 && pDurumu.P10 != 2)) digitalWrite(LED_9, LED_STATE_ON);
  if ((pDurumu.P10 == 1 || pDurumu.P11 == 1) && (pDurumu.P10 != 2 && pDurumu.P11 != 2)) digitalWrite(LED_10, LED_STATE_ON);
  if ((pDurumu.P11 == 1 || pDurumu.P12 == 1) && (pDurumu.P11 != 2 && pDurumu.P12 != 2)) digitalWrite(LED_11, LED_STATE_ON);
  if ((pDurumu.P12 == 1 || pDurumu.P13 == 1) && (pDurumu.P12 != 2 && pDurumu.P13 != 2)) digitalWrite(LED_12, LED_STATE_ON);
  if ((pDurumu.P13 == 1 || pDurumu.P14 == 1) && (pDurumu.P13 != 2 && pDurumu.P14 != 2)) digitalWrite(LED_13, LED_STATE_ON);
}

void ParkLed::blink(ParkDurumu &pDurumu) {
#ifndef LED_MASTER
  _blinkState = digitalRead(LED_SYNC);

  if (pDurumu.P1 == 2 || pDurumu.P2 == 2) digitalWrite(LED_1, _blinkState ? LED_STATE_ON : LED_STATE_OFF);
  if (pDurumu.P2 == 2 || pDurumu.P3 == 2) digitalWrite(LED_2, _blinkState ? LED_STATE_ON : LED_STATE_OFF);
  if (pDurumu.P3 == 2 || pDurumu.P4 == 2) digitalWrite(LED_3, _blinkState ? LED_STATE_ON : LED_STATE_OFF);
  if (pDurumu.P4 == 2 || pDurumu.P5 == 2) digitalWrite(LED_4, _blinkState ? LED_STATE_ON : LED_STATE_OFF);
  if (pDurumu.P5 == 2 || pDurumu.P6 == 2) digitalWrite(LED_5, _blinkState ? LED_STATE_ON : LED_STATE_OFF);
  if (pDurumu.P6 == 2 || pDurumu.P7 == 2) digitalWrite(LED_6, _blinkState ? LED_STATE_ON : LED_STATE_OFF);
  if (pDurumu.P7 == 2 || pDurumu.P8 == 2) digitalWrite(LED_7, _blinkState ? LED_STATE_ON : LED_STATE_OFF);
  if (pDurumu.P8 == 2 || pDurumu.P9 == 2) digitalWrite(LED_8, _blinkState ? LED_STATE_ON : LED_STATE_OFF);
  if (pDurumu.P9 == 2 || pDurumu.P10 == 2) digitalWrite(LED_9, _blinkState ? LED_STATE_ON : LED_STATE_OFF);
  if (pDurumu.P10 == 2 || pDurumu.P11 == 2) digitalWrite(LED_10, _blinkState ? LED_STATE_ON : LED_STATE_OFF);
  if (pDurumu.P11 == 2 || pDurumu.P12 == 2) digitalWrite(LED_11, _blinkState ? LED_STATE_ON : LED_STATE_OFF);
  if (pDurumu.P12 == 2 || pDurumu.P13 == 2) digitalWrite(LED_12, _blinkState ? LED_STATE_ON : LED_STATE_OFF);
  if (pDurumu.P13 == 2 || pDurumu.P14 == 2) digitalWrite(LED_13, _blinkState ? LED_STATE_ON : LED_STATE_OFF);

  return;
#endif

  unsigned long currentMillis = millis();
  if (_prevBlinkMillis == -1) _prevBlinkMillis = currentMillis;

  if (currentMillis - _prevBlinkMillis >= LED_BLINK_INTERVAL) {
    _prevBlinkMillis = currentMillis;
    _blinkState = !_blinkState;

    if (pDurumu.P1 == 2 || pDurumu.P2 == 2) digitalWrite(LED_1, _blinkState ? LED_STATE_ON : LED_STATE_OFF);
    if (pDurumu.P2 == 2 || pDurumu.P3 == 2) digitalWrite(LED_2, _blinkState ? LED_STATE_ON : LED_STATE_OFF);
    if (pDurumu.P3 == 2 || pDurumu.P4 == 2) digitalWrite(LED_3, _blinkState ? LED_STATE_ON : LED_STATE_OFF);
    if (pDurumu.P4 == 2 || pDurumu.P5 == 2) digitalWrite(LED_4, _blinkState ? LED_STATE_ON : LED_STATE_OFF);
    if (pDurumu.P5 == 2 || pDurumu.P6 == 2) digitalWrite(LED_5, _blinkState ? LED_STATE_ON : LED_STATE_OFF);
    if (pDurumu.P6 == 2 || pDurumu.P7 == 2) digitalWrite(LED_6, _blinkState ? LED_STATE_ON : LED_STATE_OFF);
    if (pDurumu.P7 == 2 || pDurumu.P8 == 2) digitalWrite(LED_7, _blinkState ? LED_STATE_ON : LED_STATE_OFF);
    if (pDurumu.P8 == 2 || pDurumu.P9 == 2) digitalWrite(LED_8, _blinkState ? LED_STATE_ON : LED_STATE_OFF);
    if (pDurumu.P9 == 2 || pDurumu.P10 == 2) digitalWrite(LED_9, _blinkState ? LED_STATE_ON : LED_STATE_OFF);
    if (pDurumu.P10 == 2 || pDurumu.P11 == 2) digitalWrite(LED_10, _blinkState ? LED_STATE_ON : LED_STATE_OFF);
    if (pDurumu.P11 == 2 || pDurumu.P12 == 2) digitalWrite(LED_11, _blinkState ? LED_STATE_ON : LED_STATE_OFF);
    if (pDurumu.P12 == 2 || pDurumu.P13 == 2) digitalWrite(LED_12, _blinkState ? LED_STATE_ON : LED_STATE_OFF);
    if (pDurumu.P13 == 2 || pDurumu.P14 == 2) digitalWrite(LED_13, _blinkState ? LED_STATE_ON : LED_STATE_OFF);
  }
}