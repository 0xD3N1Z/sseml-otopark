#include <Arduino.h>

#include "ParkUtils.h"
#include "Config.h"

bool buzzerPinSet = false;

uint16_t checksum(uint8_t* data, uint16_t length) {
  uint16_t curr_crc = 0x0000;

  uint8_t sum1 = (uint8_t)curr_crc;
  uint8_t sum2 = (uint8_t)(curr_crc >> 8);

  int index;

  for (index = 0; index < length; index = index + 1) {
    sum1 = (sum1 + data[index]) % 255;
    sum2 = (sum2 + sum1) % 255;
  }

  return (sum2 << 8) | sum1;
}

void printHex(byte *buffer, byte bufferSize) {
  for (byte i = 0; i < bufferSize; i++) {
    Serial.print(buffer[i] < 0x10 ? " 0" : " ");
    Serial.print(buffer[i], HEX);
  }
}

void beep(BeepCodes code = BeepCodes::OK) {
  #ifdef MUTE_BUZZER
  return;
  #endif
  
  if (!buzzerPinSet) {
    pinMode(BUZZER_PIN, OUTPUT);
    buzzerPinSet = true;
  }

  switch(code) {
    case BeepCodes::OK:
      for(int i = 1; i <= 2; i++) {
        digitalWrite(BUZZER_PIN, HIGH);
        delay(100);
        digitalWrite(BUZZER_PIN, LOW);
        delay(50);
      }
    break;

    case BeepCodes::ERROR:
      for(int i = 1; i <= 2; i++) {
        digitalWrite(BUZZER_PIN, HIGH);
        delay(300);
        digitalWrite(BUZZER_PIN, LOW);
        delay(50);
      }
    break;

    case BeepCodes::GATE:
      for(int i = 1; i <= 4; i++) {
        digitalWrite(BUZZER_PIN, HIGH);
        delay(75);
        digitalWrite(BUZZER_PIN, LOW);
        delay(25);
      }
    break;

    default:
      digitalWrite(BUZZER_PIN, HIGH);
      delay(75);
      digitalWrite(BUZZER_PIN, LOW);
    break;
  }
}