#include "Sensors/AirSensor.hpp"

AirSensor::AirSensor()
{
  air_sensor_last_read = 0;
  _temperature = 0.0;
  _humidity = 0.0;
}

void AirSensor::loop() {
  if (millis() - air_sensor_last_read >= 2000) {
    air_sensor_last_read = millis();
    // @todo Request from HWC
  }
}

float AirSensor::getTemp() {
  return _temperature;
}

float AirSensor::getHumidity() {
  return _humidity;
}
