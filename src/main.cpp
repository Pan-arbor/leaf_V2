#include <Arduino.h>
#include <LoRa_STM32.h>
#include <SPI.h>
#include "DataLogger.h"  
#include "LoRaTransmit.h" 
#include "TemperatureSensor.h"
#include <STM32LowPower.h>
#include <STM32RTC.h>

// put function declarations here:

DataLogger dataLogger;
LoRaTransmit loraTransmitter;
/* Get the rtc object */
STM32RTC& rtc = STM32RTC::getInstance();
void configureRTC();
void sleepHandler(void *data);
void dataHandle();
int counter = 0;
uint8_t seconds = 0;
uint8_t  minutes = 0;
uint8_t hours = 0;

uint8_t day = 1; 
uint8_t month = 9; 
uint8_t year = 15;   // Not used, but required for the function call

// uint8_t alarm_sec;
// uint8_t alarm_min;
// uint8_t alarm_hour;
// uint8_t set = 0;

void setup() 
{
  Serial.begin(115200);
//   Serial.println("Starting setup");
  rtc.setClockSource(STM32RTC::LSE_CLOCK);
  rtc.begin();
  rtc.setTime(hours, minutes, seconds);

} 
void loop() {

  dataHandle();
  rtc.getTime(&hours, &minutes, &seconds, nullptr, nullptr);
  String timeString = "hour: " + String(hours) + " minutes: " + String(minutes) + " seconds: " + String(seconds);
  //Serial.println(timeString);
  delay(1000);

  // Serial.println( "Go back to sleep");
  LowPower.begin();
  LowPower.deepSleep(900000);

}
// put function definitions here:

void dataHandle() {

  digitalWrite(PB6, HIGH);
  digitalWrite(PA1, HIGH);


  pinMode (tempBus, INPUT_PULLUP);
  float temp = getTemperature();
  
  loraTransmitter.setupLoRa();
  Serial.print("Starting Sending packet with temp: ");
  Serial.print(String(temp) + " at ");
  rtc.getTime(&hours, &minutes, &seconds, nullptr, nullptr);
  String timeString = String(hours) + ":" + String(minutes) + ":" + String(seconds);
  Serial.println(timeString);
  dataLogger.initSDCard();
  String message =String(counter) + "," + String(hours) + "," + String(minutes) + "," + String(seconds) + "," + String(temp) + "C";
  loraTransmitter.sendMessage(message);
  counter ++;
  dataLogger.writeLog(message, timeString);

}

