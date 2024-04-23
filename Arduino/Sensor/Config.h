#ifndef CONFIG_H
#define CONFIG_H

//Hata ayıklama
//#define DHT_DEBUG
//#define TCRT_DEBUG
//#define POWER_DEBUG
//#define LDR_DEBUG

//Seri iletişim sırasında tanıtılacak özel ID
#define SERIAL_ID "OTOPARK-SENSOR"

//Seri iletişim için kullanılacak veri iletim hızı
#define SERIAL_BAUDRATE 9600

//CRC veri bütünlüğünü hata ayıklama amacıyla atlamak için
//Sistem çalışırken açık olmalı!!
//#define SKIP_CRC

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

//DHT sensörü
#define DHT_PIN 35
#define DHT_MEASURE_INTERVAL 5000

//TCRT5000 Sensörleri için ayarlar
// - Hangi değerin altındaysa park edildi sayılacak
// - Doğrulamak için kaç ölçüm alınsın
// - Kaç ölçüm alınıp ortalaması bulunsun
// - Ölçümler arası bekleme süresi
// - Sensörleri kapatmak için kullanılan mosfetin pini
// - Hata ayıklama için yazdırma
#define TCRT_TRIGGER 700
#define TCRT_TRIGGER_SAMPLES 5
#define TCRT_MEASURE_AVG 3
#define TCRT_MEASURE_INTERVAL 1000
#define TCRT_MOSFET_PIN 2

//Güç sensörleri pinleri
// - 5V Akım sensörü
// - Solar voltaj
// - Pil voltajı
// - Solar panel kontrolü
// - 5V adaptör kontrolü
#define CURRENT_SENSOR_PIN A2
#define SOLAR_VOLTAGE_PIN A3
#define BATTERY_VOLTAGE_PIN A4
#define BATTERY_VOLTAGE_OFFSET 1.2
#define SOLAR_DETECTION_PIN 37
#define WALL_PLUG_DETECTION_PIN 39
#define POWER_MEASURE_INTERVAL 1000

//RTC Modülü
#define RTC_CLK 30
#define RTC_DAT 32
#define RTC_RST 34

//OLED Ekran
#define OLED_CLK 3
#define OLED_MOSI 4
#define OLED_RST 5
#define OLED_DC 6
#define OLED_CS 7
#define OLED_SWITCH_INTERVAL 5000

//Servolar
#define SERVO_GIRIS 8
#define SERVO_GIRIS_OPEN 90
#define SERVO_GIRIS_CLOSED 0
#define SERVO_CIKIS 9
#define SERVO_CIKIS_OPEN 90
#define SERVO_CIKIS_CLOSED 0
#define SERVO_STEP 5
#define SERVO_SPEED 25
#define SERVO_CLOSE_DELAY 5000

//LDR
#define LDR_TRIGGER 500
#define LDR_TRIGGER_SAMPLES 10
#define LDR_MEASURE_INTERVAL 200
#define LDR_GIRIS A5
#define LDR_CIKIS A6

#endif