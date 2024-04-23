#include "HardwareSerial.h"
#include <Arduino.h>  //Arduino kütüphanesi
#include <DHT.h>

#include "ParkSensorler.h"  //C++ header dosyası
#include "Config.h"   //Ayarları içeren dosya

DHT dht(DHT_PIN, DHT11);

//PUBLIC KODLAR

void ParkSensorler::init() {
  //TCRT5000
  pinMode(MUX_A, INPUT);
  pinMode(MUX_B, INPUT);
  
  pinMode(MUX_A_S0, OUTPUT);
  pinMode(MUX_A_S1, OUTPUT);
  pinMode(MUX_A_S2, OUTPUT);
  pinMode(MUX_A_S3, OUTPUT);

  pinMode(MUX_B_S0, OUTPUT);
  pinMode(MUX_B_S1, OUTPUT);
  pinMode(MUX_B_S2, OUTPUT);
  pinMode(MUX_B_S3, OUTPUT);

  pinMode(TCRT_MOSFET_PIN, OUTPUT);

  //DHT
  dht.begin();

  //LDR
  pinMode(LDR_GIRIS, INPUT);
  pinMode(LDR_CIKIS, INPUT);

  //POWER
  pinMode(WALL_PLUG_DETECTION_PIN, INPUT);
  pinMode(SOLAR_DETECTION_PIN, INPUT_PULLUP);
  pinMode(SOLAR_VOLTAGE_PIN, INPUT);
}

void ParkSensorler::handle(SensorDurumu &sensorDurum) {
  tcrt5000(sensorDurum);
  dht11(sensorDurum);
  ldr(sensorDurum);
  power(sensorDurum);
}

//PRİVATE KODLAR

void ParkSensorler::tcrt5000(SensorDurumu &sensorDurum) {
  unsigned long currentMillis = millis();

  //başlangıçta ayarla
  if (_tcrtPrevMeasureMillis == 0) _tcrtPrevMeasureMillis = currentMillis;

  //her bir aralıkta ölçüm yap
  if (currentMillis - _tcrtPrevMeasureMillis >= TCRT_MEASURE_INTERVAL) {
    _tcrtPrevMeasureMillis = currentMillis;

    digitalWrite(TCRT_MOSFET_PIN, HIGH); //Kızılötesi ışıkları yak
    delay(10);

    #ifdef TCRT_DEBUG
    Serial.print("TCRT5000-DEBUG: A: [");
    #endif

    //A bloğu ölçümleri
    for (int i = 0; i <= 13; i++) {
      mux(i, 'A'); //Multiplexer'da sensörü seç

      long sensorTotal = 0;
      for (int ii = 0; ii < TCRT_MEASURE_AVG; ii++) sensorTotal += analogRead(MUX_A);

      long sensorAvg = sensorTotal / TCRT_MEASURE_AVG; //ortalaması alınmış değer

      #ifdef TCRT_DEBUG
      Serial.print(sensorAvg);
      if (i != 13) Serial.print(", ");
      #endif

      //Tetik aralığının üstündeyse ve hala 0 olmamışsa bir çıkart
      if ((sensorAvg > TCRT_TRIGGER) && (_tcrt5000A_sampleCount[i] > 0)) _tcrt5000A_sampleCount[i]--;

      //Tetik aralığının altındaysa ve örnek sayısına ulaşılmamışsa bir arttır
      if ((sensorAvg < TCRT_TRIGGER) && (_tcrt5000A_sampleCount[i] < TCRT_TRIGGER_SAMPLES)) _tcrt5000A_sampleCount[i]++;
    }

    #ifdef TCRT_DEBUG
    Serial.print("] B: [");
    #endif

    //B bloğu ölçümleri
    for (int i = 0; i <= 13; i++) {
      mux(i, 'B'); //Multiplexer'da sensörü seç

      long sensorTotal = 0;
      for (int ii = 0; ii < TCRT_MEASURE_AVG; ii++) sensorTotal += analogRead(MUX_B);

      long sensorAvg = sensorTotal / TCRT_MEASURE_AVG; //ortalaması alınmış değer

      #ifdef TCRT_DEBUG
      Serial.print(sensorAvg);
      if (i != 13) Serial.print(", ");
      #endif

      //Tetik aralığının üstündeyse ve hala 0 olmamışsa bir çıkart
      if ((sensorAvg > TCRT_TRIGGER) && (_tcrt5000B_sampleCount[i] > 0)) _tcrt5000B_sampleCount[i]--;

      //Tetik aralığının altındaysa ve örnek sayısına ulaşılmamışsa bir arttır
      if ((sensorAvg < TCRT_TRIGGER) && (_tcrt5000B_sampleCount[i] < TCRT_TRIGGER_SAMPLES)) _tcrt5000B_sampleCount[i]++;
    }

    digitalWrite(TCRT_MOSFET_PIN, LOW); //Kızılötesi ışıkları söndür (artık işimiz yok)

    #ifdef TCRT_DEBUG
    Serial.println("]");
    #endif

    //örnek sayılarını kontrol et (A bloğu)
    for (int i = 0; i <= 13; i++) {
      if (_tcrt5000A_sampleCount[i] == TCRT_TRIGGER_SAMPLES) sensorDurum.tcrt5000A[i] = 1;
      if (_tcrt5000A_sampleCount[i] == 0) sensorDurum.tcrt5000A[i] = 0;
    }

    //örnek sayılarını kontrol et (B bloğu)
    for (int i = 0; i <= 13; i++) {
      if (_tcrt5000B_sampleCount[i] == TCRT_TRIGGER_SAMPLES) sensorDurum.tcrt5000B[i] = 1;
      if (_tcrt5000B_sampleCount[i] == 0) sensorDurum.tcrt5000B[i] = 0;
    }
  }
}

void ParkSensorler::dht11(SensorDurumu &sensorDurum) {
  unsigned long currentMillis = millis();

  //başlangıçta ayarla
  if (_dhtPrevMeasureMillis == 0) _dhtPrevMeasureMillis = currentMillis;

  //her bir aralıkta ölçüm yap
  if (currentMillis - _dhtPrevMeasureMillis >= DHT_MEASURE_INTERVAL) {
    _dhtPrevMeasureMillis = currentMillis;

    #ifdef DHT_DEBUG
    Serial.print("DHT11-DEBUG: ");
    #endif

    float sicaklik = dht.readTemperature();
    float hissedilen_sicaklik = dht.computeHeatIndex(false);
    float nem = dht.readHumidity();

    #ifdef DHT_DEBUG
    Serial.print("S: ");
    Serial.print(sicaklik);
    Serial.print(" HS: ");
    Serial.print(hissedilen_sicaklik);
    Serial.print(" N: ");
    Serial.println(nem);
    #endif

    sensorDurum.sicaklik = sicaklik;
    sensorDurum.hissedilen_sicaklik = hissedilen_sicaklik;
    sensorDurum.nem = nem; 
  }
}

void ParkSensorler::ldr(SensorDurumu &sensorDurum) {
  unsigned long currentMillis = millis();

  //başlangıçta ayarla
  if (_ldrPrevMeasureMillis == 0) _ldrPrevMeasureMillis = currentMillis;

  //her bir aralıkta ölçüm yap
  if (currentMillis - _ldrPrevMeasureMillis >= LDR_MEASURE_INTERVAL) {
    _ldrPrevMeasureMillis = currentMillis;

    #ifdef LDR_DEBUG
    Serial.print("LDR-DEBUG: [");
    #endif

    int ldr_giris = analogRead(LDR_GIRIS);
    int ldr_cikis = analogRead(LDR_CIKIS);

    #ifdef LDR_DEBUG
    Serial.print(ldr_giris);
    Serial.print(", ");
    Serial.print(ldr_cikis);
    Serial.print("]");
    #endif

    if (ldr_giris < LDR_TRIGGER) _ldr_sampleCount[0] = 0;
    if ((ldr_giris > LDR_TRIGGER) && (_ldr_sampleCount[0] < LDR_TRIGGER_SAMPLES)) _ldr_sampleCount[0]++;

    if (ldr_cikis < LDR_TRIGGER) _ldr_sampleCount[1] = 0;
    if ((ldr_cikis > LDR_TRIGGER) && (_ldr_sampleCount[1] < LDR_TRIGGER_SAMPLES)) _ldr_sampleCount[1]++;

    if (_ldr_sampleCount[0] == LDR_TRIGGER_SAMPLES) sensorDurum.ldr[0] = 1;
    if (_ldr_sampleCount[0] == 0) sensorDurum.ldr[0] = 0;

    if (_ldr_sampleCount[1] == LDR_TRIGGER_SAMPLES) sensorDurum.ldr[1] = 1;
    if (_ldr_sampleCount[1] == 0) sensorDurum.ldr[1] = 0;

    #ifdef LDR_DEBUG
    Serial.print(" DURUM: [");
    Serial.print(sensorDurum.ldr[0]);
    Serial.print(", ");
    Serial.print(sensorDurum.ldr[1]);
    Serial.println("]");
    #endif
  }
}

void ParkSensorler::power(SensorDurumu &sensorDurum) {
  unsigned long currentMillis = millis();

  //başlangıçta ayarla
  if (_powerPrevMeasureMillis == 0) _powerPrevMeasureMillis = currentMillis;

  //her bir aralıkta ölçüm yap
  if (currentMillis - _powerPrevMeasureMillis >= POWER_MEASURE_INTERVAL) {
    _powerPrevMeasureMillis = currentMillis;

    #ifdef POWER_DEBUG
    Serial.print("POWER-DEBUG: ");
    #endif

    bool wallPlugInserted = digitalRead(WALL_PLUG_DETECTION_PIN);
    bool solarInserted = digitalRead(SOLAR_DETECTION_PIN);

    float batteryVoltage = (((analogRead(BATTERY_VOLTAGE_PIN) * 5) / 1023.0) * 3) - 1.9;
    float solarVoltage = solarInserted ? ((analogRead(SOLAR_VOLTAGE_PIN) * 5) / 1023.0) : 0;

    #ifdef POWER_DEBUG
    Serial.print("PLUG_IN: ");
    Serial.print(wallPlugInserted);
    Serial.print(" SOLAR_IN: ");
    Serial.print(solarInserted);
    Serial.print(" BATT: ");
    Serial.print(batteryVoltage);
    Serial.print(" SOLAR:");
    Serial.println(solarVoltage);
    #endif

    sensorDurum.wallPlugInserted = wallPlugInserted;
    sensorDurum.solarInserted = solarInserted;
    sensorDurum.batteryVoltage = batteryVoltage;
    sensorDurum.solarVoltage = solarVoltage;
  }
}

void ParkSensorler::mux(int sensor, char block) {
  if (block == 'A') {
    digitalWrite(MUX_A_S0, _muxTable[sensor][0] - '0');
    digitalWrite(MUX_A_S1, _muxTable[sensor][1] - '0');
    digitalWrite(MUX_A_S2, _muxTable[sensor][2] - '0');
    digitalWrite(MUX_A_S3, _muxTable[sensor][3] - '0');
  }

  if (block == 'B') {
    digitalWrite(MUX_B_S0, _muxTable[sensor][0] - '0');
    digitalWrite(MUX_B_S1, _muxTable[sensor][1] - '0');
    digitalWrite(MUX_B_S2, _muxTable[sensor][2] - '0');
    digitalWrite(MUX_B_S3, _muxTable[sensor][3] - '0');
  }

  delayMicroseconds(10);
}
