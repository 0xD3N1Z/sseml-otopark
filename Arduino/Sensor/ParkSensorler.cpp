#include <Arduino.h>  //Arduino kütüphanesi

#include "ParkSensorler.h"  //C++ header dosyası
#include "Config.h"   //Ayarları içeren dosya

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
  //--
}

void ParkSensorler::handle(SensorDurumu &sensorDurum) {
  tcrt5000(sensorDurum);
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

    //A bloğu ölçümleri
    for (int i = 0; i <= 13; i++) {
      mux(i, 'A'); //Multiplexer'da sensörü seç

      long sensorTotal = 0;
      for (int ii = 0; ii < TCRT_MEASURE_AVG; ii++) sensorTotal += analogRead(MUX_A);

      long sensorAvg = sensorTotal / TCRT_MEASURE_AVG; //ortalaması alınmış değer

      //Tetik aralığının üstündeyse ve hala 0 olmamışsa bir çıkart
      if ((sensorAvg > TCRT_TRIGGER) && (_tcrt5000A_sampleCount[i] > 0)) _tcrt5000A_sampleCount[i]--;

      //Tetik aralığının altındaysa ve örnek sayısına ulaşılmamışsa bir arttır
      if ((sensorAvg < TCRT_TRIGGER) && (_tcrt5000A_sampleCount[i] < TCRT_TRIGGER_SAMPLES)) _tcrt5000A_sampleCount[i]++;
    }

    //B bloğu ölçümleri
    for (int i = 0; i <= 13; i++) {
      mux(i, 'B'); //Multiplexer'da sensörü seç

      long sensorTotal = 0;
      for (int ii = 0; ii < TCRT_MEASURE_AVG; ii++) sensorTotal += analogRead(MUX_B);

      long sensorAvg = sensorTotal / TCRT_MEASURE_AVG; //ortalaması alınmış değer

      //Tetik aralığının üstündeyse ve hala 0 olmamışsa bir çıkart
      if ((sensorAvg > TCRT_TRIGGER) && (_tcrt5000B_sampleCount[i] > 0)) _tcrt5000B_sampleCount[i]--;

      //Tetik aralığının altındaysa ve örnek sayısına ulaşılmamışsa bir arttır
      if ((sensorAvg < TCRT_TRIGGER) && (_tcrt5000B_sampleCount[i] < TCRT_TRIGGER_SAMPLES)) _tcrt5000B_sampleCount[i]++;
    }

    digitalWrite(TCRT_MOSFET_PIN, LOW); //Kızılötesi ışıkları söndür (artık işimiz yok)

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
