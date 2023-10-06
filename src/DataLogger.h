#ifndef DataLogger_h
#define DataLogger_h

#include <Arduino.h>

// Libraries for SD Card
// #include "FS.h"
#include "SdFat.h"
#include <SPI.h>

#include <Wire.h>


class DataLogger {
public:
  DataLogger();
  void initSDCard();
  void writeLog(String message);
};

#endif


