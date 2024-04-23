#ifndef CONFIG_H
#define CONFIG_H

//Seri iletişim sırasında tanıtılacak özel ID
#define SERIAL_ID "OTOPARK-SENSOR"

//Seri iletişim için kullanılacak veri iletim hızı
#define SERIAL_BAUDRATE 9600

//CRC veri bütünlüğünü hata ayıklama amacıyla atlamak için
//Sistem çalışırken açık olmalı!!
#define SKIP_CRC

//Multiplexer pinleri
// - A bloğu
// - B bloğu
#define MUX_A A1
#define MUX_A_S0 28
#define MUX_A_S1 26
#define MUX_A_S2 24
#define MUX_A_S3 22
#define MUX_B A0
#define MUX_B_S0 48
#define MUX_B_S1 46
#define MUX_B_S2 44
#define MUX_B_S3 42

//Diğer bileşenlerin pinleri
#define BUZZER_PIN 33

//TCRT5000 Sensörleri için ayarlar
// - Hangi değerin altındaysa park edildi sayılacak
// - Doğrulamak için kaç ölçüm alınsın
// - Kaç ölçüm alınıp ortalaması bulunsun
// - Ölçümler arası bekleme süresi
// - Sensörleri kapatmak için kullanılan mosfetin pini
#define TCRT_TRIGGER 700
#define TCRT_TRIGGER_SAMPLES 5
#define TCRT_MEASURE_AVG 3
#define TCRT_MEASURE_INTERVAL 1000
#define TCRT_MOSFET_PIN 2

#endif