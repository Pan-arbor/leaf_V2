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
uint8_t hours = 16;

uint8_t day = 25; 
uint8_t month = 9; 
uint8_t year = 15;   // Not used, but required for the function call

uint8_t alarm_sec;
uint8_t alarm_min;
uint8_t alarm_hour;
uint8_t set = 0;

void setup() 
{
  Serial.begin(115200);
//   Serial.println("Starting setup");
  rtc.begin();
  rtc.setTime(hours, minutes, seconds);
//   //configureRTC();
//   rtc.attachInterrupt(sleepHandler);
//   rtc.setAlarmDay(day);
//   rtc.setAlarmTime(16, 0, 10, 123);
//   rtc.enableAlarm(rtc.MATCH_DHHMMSS);

// //   while(!rtc.isAlarmEnabled()){
// //   set += 5;
// //   Serial.print("rtc is not enabled set: ");
// //   Serial.println(set);
// //   rtc.setAlarmTime(16, 0, set, 123);
// //   rtc.enableAlarm(rtc.MATCH_DHHMMSS);
// //   delay(1000);
// // }
//   Serial.println("alarm is enabled");
} 
void loop() {

  dataHandle();
  rtc.getTime(&hours, &minutes, &seconds, nullptr, nullptr);

  Serial.println("hour: " + String(hours) + " minutes: " + String(minutes) + " seconds: " + String(seconds));
  delay(1000);

  // Serial.println( "Go back to sleep");

  // LoRa.sleep();
   LowPower.begin();
   LowPower.deepSleep(60000);

}
// put function definitions here:

// void configureRTC() {

//   rtc.getTime(&alarm_hour, &alarm_min, &alarm_sec, nullptr, nullptr);

//   alarm_sec += 10;
//   if (alarm_sec >= 60) {
//     alarm_sec -= 60;
//     alarm_min++;

//     if (alarm_min >= 60) {
//       alarm_min -= 60;
//       alarm_hour++;

//       if (hours >= 24) {
//         hours = 0;
//       }
//     }
//   Serial.println("Alarm Configured and Enabled for 5 seconds");
// }
// }

// void sleepHandler(void *data) {
//   // Handle what to do when MCU wakes up
//   Serial.println("wake up");// Reconfigure the RTC alarm for the next wake-up
//   UNUSED(data);
//   dataHandle();
//   configureRTC();
//   rtc.setAlarmTime(alarm_hour, alarm_min, alarm_sec, 123);
//   rtc.enableAlarm(rtc.MATCH_HHMMSS);
// }

void dataHandle() {

  digitalWrite(PB6, HIGH);
  digitalWrite(PA1, HIGH);


  pinMode (tempBus, INPUT_PULLUP);
  float temp = getTemperature();
  String message = "index " + String(counter) + " Temperature: " + String(temp) + "C";
  
  loraTransmitter.setupLoRa();
  Serial.print("Starting Sending packet: ");
  Serial.println(message);
  loraTransmitter.sendMessage(message);
  counter ++;
  delay(1000);

  dataLogger.initSDCard();
  dataLogger.writeLog(message);
  delay(1000);
}

