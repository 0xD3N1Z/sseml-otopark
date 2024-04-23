#ifndef CONFIG_H
#define CONFIG_H

//Seri iletişim sırasında tanıtılacak özel ID
#define SERIAL_ID "OTOPARK-LED-A"

//Seri iletişim için kullanılacak veri iletim hızı
#define SERIAL_BAUDRATE 9600

//CRC veri bütünlüğünü hata ayıklama amacıyla atlamak için
//Sistem çalışırken açık olmalı!!
#define SKIP_CRC

//Ledleri kontrol eden diğer arduinoları eşitlemek için kullanılıyorsa (Master cihaz)
//A Bloğu dışında kapalı olması lazım
#define LED_MASTER

//Park çizgisi ışıklarının bağlandığı pinler
//11 adet dijital, 2 adet analog çıkış
#define LED_1 A5
#define LED_2 A4
#define LED_3 2
#define LED_4 3
#define LED_5 4
#define LED_6 5
#define LED_7 6
#define LED_8 7
#define LED_9 8
#define LED_10 9
#define LED_11 10
#define LED_12 11
#define LED_13 12

//Ledlerin yanıp sönmesini eşitlemek için kullanılacak pin
#define LED_SYNC A0

//Boş park alanı gösterilirken LED'lerin ne kadar sıklıkta ve
//ne kadar süre yanık kalacağı
#define LED_BLINK_INTERVAL 500
//#define LED_BLINK_DURATION 100

//Ledlerin hangi lojik seviyelerinde açık/kapalı olacağı
#define LED_STATE_ON 1
#define LED_STATE_OFF 0

#endif