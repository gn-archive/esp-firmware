#include "Sensors/Sensors.hpp"

SensorsClass::SensorsClass():
waterLevelNode("water_level", "LOW or OK"),
airSensorNode("air_sensor", "temperature F and RH"),
waterTempNode("water_temp", "degrees F"),
air_sensor(),
water_temp_sensor()
{
  dataLastSentAt = 0;
}
SensorsClass Sensors;

void SensorsClass::setup() {
  airSensorNode.advertise("temperature");
  airSensorNode.advertise("humidity");
  waterLevelNode.advertise("level");
  waterTempNode.advertise("temperature");

  water_temp_sensor.setup();
}

void SensorsClass::loop() {
  air_sensor.loop();
  water_temp_sensor.loop();
  water_level_sensor.loop();

  if (millis() - dataLastSentAt > SEND_SENSOR_DATA_INTERVAL) {
    dataLastSentAt = millis();
    uploadCurrentState();
  }
}


void SensorsClass::uploadCurrentState() {
  Serial.print("Air temperature: ");
  Serial.print(air_sensor.getTemp());
  Serial.print(" °F, humidity: ");
  Serial.print(air_sensor.getHumidity());
  Serial.println("% RH");
  Serial.print("Water temperature: ");
  Serial.print(water_temp_sensor.getTemp());
  Serial.println(" °F");
  Serial.print("Water level: ");
  Serial.println(water_level_sensor.waterLevelLow() ? "LOW" : "OK");

  if (!Homie.isConnected()) {
		return;
	}
  airSensorNode.setProperty("temperature").send(String(air_sensor.getTemp()));
  airSensorNode.setProperty("humidity").send(String(air_sensor.getHumidity()));
  waterTempNode.setProperty("temperature").send(String(water_temp_sensor.getTemp()));
  waterLevelNode.setProperty("level").send(water_level_sensor.waterLevelLow() ? "LOW" : "OK");

}
