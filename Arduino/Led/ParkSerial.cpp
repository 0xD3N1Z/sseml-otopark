#include <Arduino.h>

#include "ParkSerial.h"
#include "ParkLed.h"
#include "ParkUtils.h"
#include "Config.h"

void ParkSerial::init() {
  Serial.begin(SERIAL_BAUDRATE);
}

void ParkSerial::handle(ParkDurumu &pDurumu) {
  if (Serial.available()) {
    _serialcmd = Serial.readStringUntil('\n');
    _serialcmd.trim();
  }

  if (_serialcmd != "") {
    bool response = false;

    //Raspberry Pi Seri kimliği sorarsa
    if (_serialcmd.equals("SERIAL-ID?")) {
      response = true;

      Serial.println(SERIAL_ID);
    }

    //Raspberry Pi üzerinden gelen LED komutu
    if (_serialcmd.startsWith("LED-CMD:")) {
      response = true;

      char park_alanlari[14];
      for (int i = 8;; i++) {
        char n = _serialcmd[i];

        if (n == ';') break;
        if (n != '0' & n != '1' & n != '2') n = '0'; //hatalıysa 0 yap

        park_alanlari[i - 8] = n;
      }

      uint16_t checksumm = checksum(park_alanlari, 14);
      Serial.println(checksumm, HEX);

      Serial.println(park_alanlari);
    }

    //Geçersiz komut
    if (!response) Serial.println("CMD-ERROR");

    _serialcmd = "";
  }
}