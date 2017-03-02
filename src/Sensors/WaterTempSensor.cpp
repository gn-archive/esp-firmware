#include "Sensors/WaterTempSensor.hpp"

WaterTempSensor::WaterTempSensor():
bus(ONE_WIRE_BUS),
sensors(&bus)
{
  temperature = 0;
  last_read = 0;
}

void WaterTempSensor::setup() {
  sensors.begin();
  sensors.setWaitForConversion(false);  // makes it async
}

void WaterTempSensor::loop() {
  if (millis() - last_read >= 4000) {
    last_read = millis();
    readSensor();
  }
}

float WaterTempSensor::getTemp() {
  return temperature == -127.0 ? 0.0 : temperature * 9/5+32;
}

void WaterTempSensor::readSensor() {

  sensors.requestTemperatures(); // Send the command to get temperatures
  // We use the function ByIndex, and as an example get the temperature from the first sensor only.
  float new_temperature = sensors.getTempCByIndex(0);

  if (isnan(new_temperature)) {
    Serial.println("Failed to read water temp sensor!");
  } else {
    temperature = new_temperature;
  }
}
