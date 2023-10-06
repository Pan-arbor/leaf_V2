#include "DataLogger.h"

#define CHIP_SELECT_PIN PB6

SdFat sd;
SdFile file;

DataLogger::DataLogger() {
  
}

void DataLogger::initSDCard() {
  // Initialize the SD card
  pinMode(CHIP_SELECT_PIN, OUTPUT);
  digitalWrite(CHIP_SELECT_PIN, LOW);
  SPI.setMOSI(PB15);
  SPI.setMISO(PB14);
  SPI.setSCLK(PB13);
  SPI.begin(CHIP_SELECT_PIN);
  while (!sd.begin(CHIP_SELECT_PIN)) {

    SPI.begin(CHIP_SELECT_PIN);
    Serial.println("SDcard not working");
    delay(1000);
    sd.initErrorHalt();
  }
  
  Serial.println("Initialization done.");
  delay(1000);
}

void DataLogger::writeLog(String message) {

  if (!sd.exists("log.txt")) {
    Serial.println("Creating log.txt");
    File logFile = sd.open("log.txt", O_RDWR | O_CREAT | O_AT_END);
    if (logFile){

      logFile.close();
    } else {
      Serial.println("Could not create log.txt");
      return;
    }
  }

  File logFile = sd.open("log.txt", O_RDWR | O_CREAT | O_AT_END);
  if (logFile) {
    logFile.println(message);
    logFile.close();
    Serial.println("Log written");
  } else {
    Serial.println("Error opening log.txt");
  }
  
  SPI.end();
  sd.end();
  
  //digitalWrite(CHIP_SELECT_PIN, HIGH); 
}

