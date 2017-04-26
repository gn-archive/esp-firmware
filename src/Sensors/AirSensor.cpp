#include "Sensors/AirSensor.hpp"

AirSensor::AirSensor()
{
  air_sensor_data.temperature = 0.0;
  air_sensor_data.humidity = 0.0;
  air_sensor_data.last_read = 0;
  air_sensor_data.last_read_success = false;
}

void AirSensor::byte_to_struct_2(byte *a) {
    struct AirSensorData *temp = (struct AirSensorData*)a;
    air_sensor_data.temperature = temp->temperature;
    air_sensor_data.humidity = temp->humidity;
    air_sensor_data.last_read = temp->last_read;
    air_sensor_data.last_read_success = temp->last_read_success;
}

void AirSensor::loop() {
  if (millis() - air_sensor_data.last_read >= 2000) {
    byte buf [10]; // guess 10 bytes?

    if (Wire.requestFrom (HWC_I2C_ID, 10)) { //10 bytes?
      // if request succeeded
      for (byte i = 0; i < 10; i++) //10 bytes?
        buf [i] = Wire.read ();

      byte_to_struct_2(buf);
    }
    else {
      Serial.println(F("I2C failed"));
    }
  }
}

float AirSensor::getTemp() {
  return air_sensor_data.temperature;
}

float AirSensor::getHumidity() {
  return air_sensor_data.humidity;
}
