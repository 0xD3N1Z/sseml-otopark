#include "HardwareSerial.h"
#include "Print.h"
#include <Arduino.h>

#include "ParkSerial.h"
#include "ParkSensorler.h"
#include "ParkCihazlar.h"
#include "ParkUtils.h"
#include "Config.h"

void ParkSerial::init() {
  Serial.begin(SERIAL_BAUDRATE);
}

void ParkSerial::handle(SensorDurumu &sensorDurum, CihazDurumu &cihazDurum) {
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

      //A bloğu bilgileri için hesaplanan CRC değeri
      _tcrt5000A_str = "";
      for (int i = 0; i <= 13; i++) _tcrt5000A_str += sensorDurum.tcrt5000A[i] == 1 ? '1' : '0';
      uint16_t crc_A = checksum((uint8_t*)_tcrt5000A_str.c_str(), 14);
      _crc_a_str = String(crc_A, HEX);
      _crc_a_str.toUpperCase();

      //B bloğu bilgileri için hesaplanan CRC değeri
      _tcrt5000B_str = "";
      for (int i = 0; i <= 13; i++) _tcrt5000B_str += sensorDurum.tcrt5000B[i] == 1 ? '1' : '0';
      uint16_t crc_B = checksum((uint8_t*)_tcrt5000B_str.c_str(), 14);
      _crc_b_str = String(crc_B, HEX);
      _crc_b_str.toUpperCase();

      //Seriye yazdır
      Serial.print("PARK-SENSOR:");
      Serial.print(_tcrt5000A_str);
      Serial.print(";");
      Serial.print(_crc_a_str);
      Serial.print(";");
      Serial.print(_tcrt5000B_str);
      Serial.print(";");
      Serial.print(_crc_b_str);
      Serial.println(";");
    }

    //Raspberry Pi hava durumu bilgilerini almak istediğinde
    if (_serialcmd.equals("WEATHER-SENSOR?")) {
      response = true;

      Serial.print("WEATHER-SENSOR:");
      Serial.print(sensorDurum.sicaklik);
      Serial.print(";");
      Serial.print(sensorDurum.hissedilen_sicaklik);
      Serial.print(";");
      Serial.print(sensorDurum.nem);
      Serial.println(";");
    }

    //Raspberry Pi güç bilgilerini almak istediğinde
    if (_serialcmd.equals("POWER-SENSOR?")) {
      response = true;

      Serial.print("POWER-SENSOR:");
      Serial.print(sensorDurum.wallPlugInserted);
      Serial.print(";");
      Serial.print(sensorDurum.solarInserted);
      Serial.print(";");
      Serial.print(sensorDurum.batteryVoltage);
      Serial.print(";");
      Serial.print(sensorDurum.solarVoltage);
      Serial.println(";");
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

    if (_serialcmd.equals("GATE-ENTER")) {
      response = true;

      cihazDurum.giris_servo = true;
      beep(BeepCodes::GATE);
    }

    if (_serialcmd.equals("GATE-EXIT")) {
      response = true;

      cihazDurum.cikis_servo = true;
      beep(BeepCodes::GATE);
    }

    //Geçersiz komut
    if (!response) Serial.println("CMD-ERROR");

    clearserial:
    _serialcmd = "";
  }
}