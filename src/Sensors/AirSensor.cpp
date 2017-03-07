#include "Sensors/AirSensor.hpp"

AirSensor::AirSensor():
_air_temp(5),
_air_humidity(5)
{
  air_sensor_last_read = 0;
}

void AirSensor::loop() {
  if (millis() - air_sensor_last_read >= 2000) {
    air_sensor_last_read = millis();
    readSensor();
  }
}

float AirSensor::getTemp() {
  return _air_temp.getMedian();
}

float AirSensor::getHumidity() {
  return _air_humidity.getMedian();
}

void AirSensor::readSensor() {
  int chk = _air_sensor.read22(AIR_SENSOR_PIN);

  switch (chk)
  {
  case DHTLIB_OK:
      _air_temp.add(_air_sensor.temperature * 9/5 +32);
      _air_humidity.add(_air_sensor.humidity);
      break;
  case DHTLIB_ERROR_CHECKSUM:
      Serial.println("DHT checksum error");
      break;
  case DHTLIB_ERROR_TIMEOUT:
      Serial.println("DHT time out error");
      break;
  default:
      Serial.println("DHT unknown error");
      break;
  }


}
