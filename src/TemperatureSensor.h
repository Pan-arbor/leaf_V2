#ifndef TemperatureSensor_h
#define TemperatureSensor_h
#define tempBus PB8

#include <OneWire.h>
#include <DallasTemperature.h>

float getTemperature();


#endif
