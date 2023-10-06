#include "LoRaTransmit.h"

LoRaTransmit::LoRaTransmit() {
}

void LoRaTransmit::setupLoRa() 
{
    //Serial.begin(115200);
    while (!Serial);

    // Initialize SPI:
    SPI.setMOSI(PA7);
    SPI.setMISO(PA6);
    SPI.setSCLK(PA5);
    SPI.begin(ss);
    // Set SPI frequency (you may need to adjust this):
    //SPI.setClockDivider(SPI_CLOCK_DIV16);  // For example, divide the system clock by 16
    // Set data mode (you may need to adjust this):
    //SPI.setDataMode(SPI_MODE0);  // Check the LoRa module datasheet for the correct mode.

    
    Serial.println("LoRa Sender");
    digitalWrite(ss, LOW);
    LoRa.setTxPower(TX_P);
    LoRa.setSyncWord(ENCRYPT);

    LoRa.setPins(ss, rst, dio0);

    while(!LoRa.begin(915E6)) 
    {
    Serial.println("Starting LoRa failed!");
    delay(1000);
    }

}

void LoRaTransmit::sendMessage(String message) {
  // Send message
  LoRa.beginPacket();
  LoRa.print(message);
  LoRa.endPacket();
  LoRa.end();
  digitalWrite(ss, HIGH);
  SPI.end();
}

