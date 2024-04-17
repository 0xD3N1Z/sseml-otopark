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

      int led_start_index = _serialcmd.indexOf(':') + 1;
      int crc_start_index = _serialcmd.indexOf(';') + 1;

      if (led_start_index != 8 || crc_start_index != 23) {
        Serial.println("FORMAT-ERR");
        goto clearserial;
      }

      //Park alanı bilgileri
      char park_alanlari[14];
      for (int i = led_start_index;; i++) {
        char n = _serialcmd[i];

        if (n == ';') break;
        if (n != '0' & n != '1' & n != '2') n = '0'; //hatalıysa 0 yap

        park_alanlari[i - led_start_index] = n;
      }
      
      //Hesaplanan CRC değeri
      uint16_t crc = checksum((uint8_t*)park_alanlari, 14);
      _crcstr = String(crc, HEX);
      _crcstr.toUpperCase();

      //Seri iletişim üzerinden gelen CRC değeri
      char serial_crc[4];
      for (int i = crc_start_index;; i++) {
        char n = _serialcmd[i];

        if (n == ';') break;

        serial_crc[i - crc_start_index] = n;
      }

      //CRC değerlerini karşılaştır
      bool crc_match = true;
      for (int i = 0; i <= 3; i++) {
        char crc_n = _crcstr[i];
        char serial_n = serial_crc[i];

        if (crc_n != serial_n) {
          crc_match = false;
          break;
        }
      }

      if (!crc_match) {
        Serial.println("CRC-ERR");
        goto clearserial;
      }

      //Park bilgilerini ayarla
      pDurumu.P1 = park_alanlari[0] - '0';
      pDurumu.P2 = park_alanlari[1] - '0';
      pDurumu.P3 = park_alanlari[2] - '0';
      pDurumu.P4 = park_alanlari[3] - '0';
      pDurumu.P5 = park_alanlari[4] - '0';
      pDurumu.P6 = park_alanlari[5] - '0';
      pDurumu.P7 = park_alanlari[6] - '0';
      pDurumu.P8 = park_alanlari[7] - '0';
      pDurumu.P9 = park_alanlari[8] - '0';
      pDurumu.P10 = park_alanlari[9] - '0';
      pDurumu.P11 = park_alanlari[10] - '0';
      pDurumu.P12 = park_alanlari[11] - '0';
      pDurumu.P13 = park_alanlari[12] - '0';
      pDurumu.P14 = park_alanlari[13] - '0';
    }

    //Geçersiz komut
    if (!response) Serial.println("CMD-ERROR");

    clearserial:
    _serialcmd = "";
  }
}