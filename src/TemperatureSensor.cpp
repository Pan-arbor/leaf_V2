#include "TemperatureSensor.h"


OneWire oneWire(tempBus);
DallasTemperature sensors(&oneWire);


float getTemperature() {
    sensors.begin();
    sensors.requestTemperatures(); 
    return sensors.getTempCByIndex(0);
}
