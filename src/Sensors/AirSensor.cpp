#include "Sensors/AirSensor.hpp"

AirSensor::AirSensor():
air_sensor(AIR_SENSOR_PIN, AIR_SENSOR_TYPE)
{
  air_temp = 0;
  air_sensor_last_read = 0;
}

void AirSensor::loop() {
  if (millis() - air_sensor_last_read >= 5000) {
    air_sensor_last_read = millis();
    readSensor();
  }
}

float AirSensor::getAirTemp() {
  return isnan(air_temp) ? 0.0 : air_temp;
}

float AirSensor::getAirHumidity() {
  return isnan(air_humidity) ? 0.0 : air_humidity;
}

void AirSensor::readSensor() {
  float new_air_temp_f = air_sensor.readTemperature(true);

  if (isnan(new_air_temp_f)) {
    Serial.println("Failed to read air_sensor!");
  } else {
    air_temp = new_air_temp_f;

    Serial << "Temperature: " << air_temp << " °F" << endl;
  }
}
