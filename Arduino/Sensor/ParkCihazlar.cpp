#include <Arduino.h>

#include <Servo.h>
#include <RtcDS1302.h>

#include "ParkCihazlar.h"
#include "ParkEkran.h"
#include "ParkSensorler.h"
#include "ParkUtils.h"
#include "Config.h"

Servo giris_servo;
Servo cikis_servo;

ThreeWire myWire(RTC_DAT, RTC_CLK, RTC_RST); // IO, SCLK, CE
RtcDS1302<ThreeWire> Rtc(myWire);

void ParkCihazlar::init() {
  giris_servo.attach(SERVO_GIRIS);
  cikis_servo.attach(SERVO_CIKIS);

  giris_servo.write(SERVO_GIRIS_CLOSED);
  cikis_servo.write(SERVO_CIKIS_CLOSED);

  Rtc.Begin();
}

void ParkCihazlar::handle(SensorDurumu &sensorDurum, CihazDurumu &cihazDurum) {
  servo(sensorDurum, cihazDurum);
  rtc(cihazDurum);
}

void ParkCihazlar::servo(SensorDurumu &sensorDurum, CihazDurumu &cihazDurum) {
  unsigned long currentMillis = millis();

  if (currentMillis - _prevServoMillis >= 100) {
    _prevServoMillis = currentMillis;

    if (cihazDurum.giris_servo && !cihazDurum.giris_bekleme) giris_servo.write(SERVO_GIRIS_OPEN);
    if (cihazDurum.cikis_servo && !cihazDurum.cikis_bekleme) cikis_servo.write(SERVO_CIKIS_OPEN);

    if (!cihazDurum.giris_servo) giris_servo.write(SERVO_GIRIS_CLOSED);
    if (!cihazDurum.cikis_servo) cikis_servo.write(SERVO_CIKIS_CLOSED);

    if (cihazDurum.giris_servo && sensorDurum.ldr[0] == 1 && !cihazDurum.giris_bekleme) cihazDurum.giris_bekleme = true;
    if (cihazDurum.cikis_servo && sensorDurum.ldr[1] == 1 && !cihazDurum.cikis_bekleme) cihazDurum.cikis_bekleme = true;
  }

  if (currentMillis - _prevServoWaitMillis >= SERVO_CLOSE_DELAY) {
    _prevServoWaitMillis = currentMillis;

    if (cihazDurum.giris_bekleme && sensorDurum.ldr[0] == 0) {
      cihazDurum.giris_servo = false;
      cihazDurum.giris_bekleme = false;
    }

    if (cihazDurum.cikis_bekleme && sensorDurum.ldr[1] == 0) {
      cihazDurum.cikis_servo = false;
      cihazDurum.cikis_bekleme = false;
    }
  }
}

void ParkCihazlar::rtc(CihazDurumu &cihazDurum) {
  unsigned long currentMillis = millis();

  if (currentMillis - _prevRtcMillis >= 100) {
    _prevRtcMillis = currentMillis;

    cihazDurum.rtc_date = Rtc.GetDateTime();
  }
}