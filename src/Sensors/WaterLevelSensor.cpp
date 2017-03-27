#include "Sensors/WaterLevelSensor.hpp"

WaterLevelSensor::WaterLevelSensor()
{
  _water_level = 0;
  _last_read = 0;
}

void WaterLevelSensor::setup() {
  ads.begin();
}

void WaterLevelSensor::loop() {
  if (millis() - _last_read >= 2000) {
    _last_read = millis();
    _water_level = ads.readADC_SingleEnded(0);
  }
}

int16_t WaterLevelSensor::getWaterLevel() {
  return _water_level;
}

bool WaterLevelSensor::waterLevelLow() {
  return _water_level < 9000;
}
