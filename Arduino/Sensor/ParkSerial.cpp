#include <Arduino.h>

#include "ParkSerial.h"
#include "ParkUtils.h"
#include "Config.h"

void ParkSerial::init() {
  Serial.begin(SERIAL_BAUDRATE);
}

void ParkSerial::handle() {
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

    // -- SENSORLER --

    //Raspberry Pi dolu ve boş park alanlarını kontrol etmek istediğinde
    if (_serialcmd.equals("PARK-SENSOR?")) {
      response = true;

      Serial.println("tcrt5000 sensör ölçümleri yap");
    }

    //Raspberry Pi hava durumu bilgilerini almak istediğinde
    if (_serialcmd.equals("WEATHER-SENSOR?")) {
      response = true;

      Serial.println("DHT11 modülünden hava durumunu oku");
    }

    //Raspberry Pi güç bilgilerini almak istediğinde
    if (_serialcmd.equals("POWER-SENSOR?")) {
      response = true;

      Serial.println("Birçok sensörden güç bilgilerini al");
    }

    // -- MODÜLLER --

    //Raspberry Pi güncel zaman bilgisini almak istediğinde
    if (_serialcmd.equals("DATE-TIME?")) {
      response = true;

      Serial.println("RTC modülünden saati oku");
    }

    //Raspberry Pi RTC modülündeki zaman bilgisini güncellemek istediğinde
    if (_serialcmd.startsWith("DATE-TIME:")) {
      response = true;

      Serial.println("RTC modülüne yeni saati yazdır");
    }


    //Geçersiz komut
    if (!response) Serial.println("CMD-ERROR");

    clearserial:
    _serialcmd = "";
  }
}