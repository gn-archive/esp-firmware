#include "Sensors/WaterLevelSensor.hpp"

WaterLevelSensor::WaterLevelSensor()
{
  _water_level = 254;
  _last_read = 0;
}

void WaterLevelSensor::loop() {
  if (millis() - _last_read >= 2000) {
    _last_read = millis();
    Wire.requestFrom(8, 1);    // request 6 bytes from slave device #8
    _water_level = Wire.read();
  }
}

uint8_t WaterLevelSensor::getWaterLevel() {
  return _water_level;
}

bool WaterLevelSensor::waterLevelLow() {
  return _water_level < 70;
}
