#include "Sensors/AirSensor.hpp"

AirSensor::AirSensor():
air_sensor(AIR_SENSOR_PIN, AIR_SENSOR_TYPE)
{
  air_temp = 0;
  air_humidity = 0;
  air_sensor_last_read = 0;
}

void AirSensor::loop() {
  if (millis() - air_sensor_last_read >= 2000) {
    air_sensor_last_read = millis();
    readSensor();
  }
}

float AirSensor::getTemp() {
  return isnan(air_temp) ? 0.0 : air_temp;
}

float AirSensor::getHumidity() {
  return isnan(air_humidity) ? 0.0 : air_humidity;
}

void AirSensor::readSensor() {
  float new_air_temp = air_sensor.readTemperature(true);
  float new_air_humidity = air_sensor.readHumidity();

  if (isnan(new_air_temp)) {
    Serial.println("Failed to read air_sensor!");
  } else {
    air_temp = new_air_temp;
    air_humidity = new_air_humidity;
  }
}
