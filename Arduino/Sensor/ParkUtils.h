#ifndef PARKUTILS_H
#define PARKUTILS_H

enum class BeepCodes {
  STARTUP, OK, ERROR, ACTION, GATE
};

void beep(BeepCodes code);

uint16_t checksum(uint8_t* data, uint16_t length);

void printHex(byte *buffer, byte bufferSize);

#endif