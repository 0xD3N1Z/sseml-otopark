#include <Arduino.h>

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>
#include <RtcDS1302.h>

#include "ParkEkran.h"
#include "ParkSensorler.h"
#include "ParkCihazlar.h"
#include "Config.h"

Adafruit_SH1106G display = Adafruit_SH1106G(128, 64, OLED_MOSI, OLED_CLK, OLED_DC, OLED_RST, OLED_CS);

void ParkEkran::init() {
  display.begin(0, true);
  sseml();
}

void ParkEkran::handle(SensorDurumu &sensorDurum, CihazDurumu &cihazDurum) {
  unsigned long currentMillis = millis();

  if (currentMillis - _prevPageSwitchMillis >= OLED_SWITCH_INTERVAL) {
    _prevPageSwitchMillis = currentMillis;

    if (_currentPageIndex == 3) _currentPageIndex = 0;
    else _currentPageIndex++;

    switch(_currentPageIndex) {
      case 0: sseml(); break;
      case 1: doluluk(sensorDurum); break;
      case 2: saat_hava_durumu(sensorDurum, cihazDurum); break;
      case 3: guc_bilgisi(sensorDurum); break;
    }
  }
}

void ParkEkran::sseml() {
  display.clearDisplay();
  display.setTextSize(3);
  display.setTextColor(SH110X_WHITE);

  display.setCursor(20, 10);
  display.write("SSEML OTOPARK");

  display.display();
}

void ParkEkran::doluluk(SensorDurumu &sensorDurum) {
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(SH110X_WHITE);

  int dolu_park_alanlari = 0;
  for (int i = 0; i <= 13; i++) if (sensorDurum.tcrt5000A[i] == 1) dolu_park_alanlari++;
  for (int i = 0; i <= 13; i++) if (sensorDurum.tcrt5000B[i] == 1) dolu_park_alanlari++;

  display.setCursor(0, 0);
  display.print("\n ");
  display.print(dolu_park_alanlari);
  display.println("/28 Dolu");

  display.setTextSize(1);
  display.print("\n");
  display.print(dolu_park_alanlari);
  display.println(" adet dolu park yeri");
  display.print(28 - dolu_park_alanlari);
  display.println(" adet bos park yeri");

  display.display();
}

void ParkEkran::saat_hava_durumu(SensorDurumu &sensorDurum, CihazDurumu &cihazDurum) {
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(SH110X_WHITE);
  display.setCursor(0, 0);

  display.print("\n  ");
  display.print(cihazDurum.rtc_date.Hour());
  display.print(":");
  display.print(cihazDurum.rtc_date.Minute());
  display.println(cihazDurum.rtc_date.Hour() <= 12 ? " AM" : "PM");

  display.setTextSize(1);
  display.print("\n      ");
  display.print(cihazDurum.rtc_date.Day());
  display.print(".");
  display.print(cihazDurum.rtc_date.Month());
  display.print(".");
  display.println(cihazDurum.rtc_date.Year());

  display.print("\n   S: ");
  display.print(sensorDurum.sicaklik);
  display.print(" N: ");
  display.println(sensorDurum.nem);

  display.display();
}

void ParkEkran::guc_bilgisi(SensorDurumu &sensorDurum) {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SH110X_WHITE);
  display.setCursor(0, 0);

  display.print("KABLO: ");
  display.println(sensorDurum.wallPlugInserted ? "TAKILI": "TAKILI DEGIL");

  display.print("\nSOLAR: ");
  display.println(sensorDurum.solarInserted ? "TAKILI": "TAKILI DEGIL");

  display.print("\nPIL_V: ");
  display.println(sensorDurum.batteryVoltage);

  display.print("\nSOLAR_V: ");
  display.println(sensorDurum.solarVoltage);

  display.display();
}