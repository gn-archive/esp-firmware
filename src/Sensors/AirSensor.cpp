#include "Sensors/AirSensor.hpp"

AirSensor::AirSensor():
_air_sensor(AIR_SENSOR_PIN, AIR_SENSOR_TYPE),
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
  float new_air_temp = _air_sensor.readTemperature(true);
  float new_air_humidity = _air_sensor.readHumidity();

  if (isnan(new_air_temp)) {
    Serial.println("Failed to read _air_sensor!");
  } else {
    _air_temp.add(new_air_temp);
    _air_humidity.add(new_air_humidity);
  }
}
