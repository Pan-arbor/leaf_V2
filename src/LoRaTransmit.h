#ifndef LoRaTransmit_h
#define LoRaTransmit_h

#include <Arduino.h>
#include <LoRa_STM32.h>
#include <SPI.h>
#define ss PA1
#define rst PB0
#define dio0 PA4

#define TX_P 17 
//#define BAND 915E6
#define ENCRYPT 0x78
class LoRaTransmit {
public:
  LoRaTransmit();
  void setupLoRa();
  void sendMessage(String message);
};

#endif
