#include "Sensors/WaterTempSensor.hpp"

WaterTempSensor::WaterTempSensor():
_bus(ONE_WIRE_BUS),
_temp_sensors(&_bus),
_temperature(5) // RunningMedian with 5 samples
{
  last_read = 0;
}

void WaterTempSensor::setup() {
  _temp_sensors.begin();
  _temp_sensors.setWaitForConversion(false);  // makes it async
}

void WaterTempSensor::loop() {
  if (millis() - last_read >= 4000) {
    last_read = millis();
    readSensor();
  }
}

float WaterTempSensor::getTemp() {
  return _temperature.getMedian() * 9/5 + 32;
}

void WaterTempSensor::readSensor() {

  _temp_sensors.requestTemperatures(); // Send the command to get temperatures
  // We use the function ByIndex, and as an example get the temperature from the first sensor only.
  float new_temperature = _temp_sensors.getTempCByIndex(0);

  if (isnan(new_temperature)) {
    Serial.println("Failed to read water temp sensor!");
  } else {
    _temperature.add(new_temperature);
  }
}
