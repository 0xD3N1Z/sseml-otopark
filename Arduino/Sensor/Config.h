#ifndef CONFIG_H
#define CONFIG_H

//Seri iletişim sırasında tanıtılacak özel ID
#define SERIAL_ID "OTOPARK-SENSOR"

//Seri iletişim için kullanılacak veri iletim hızı
#define SERIAL_BAUDRATE 9600

//CRC veri bütünlüğünü hata ayıklama amacıyla atlamak için
//Sistem çalışırken açık olmalı!!
#define SKIP_CRC

#endif