#include "Sensors/WaterLevelSensor.hpp"

WaterLevelSensor::WaterLevelSensor()
{
  _water_level_low = false;
  _last_read = 0;
}

void WaterLevelSensor::loop() {
  if (millis() - _last_read >= 2000) {
    _last_read = millis();
    Wire.requestFrom(8, 1);    // request 6 bytes from slave device #8
    uint8_t water_level = Wire.read();
    _water_level_low = water_level < 70;
    Serial.print("Water level: ");
    Serial.println(_water_level_low ? "LOW" : "OK");         // print the character
  }
}

bool WaterLevelSensor::getWaterLevel() {
  return _water_level_low;
}
