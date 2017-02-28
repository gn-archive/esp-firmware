#include "Sensors/Sensors.hpp"

SensorsClass::SensorsClass():
waterLevelNode("water_level", "gallons"),
airSensorNode("air_sensor", "temperature F and RH"),
waterTempNode("water_temp", "degrees F"),
air_sensor()
{
}
SensorsClass Sensors;

void SensorsClass::setup() {
  airSensorNode.advertise("temperature");
  airSensorNode.advertise("humidity");
  waterLevelNode.advertise("gallons");
  waterTempNode.advertise("degrees");
}

void SensorsClass::loop() {
  air_sensor.loop();
}


void SensorsClass::uploadCurrentState() {
  if (!Homie.isConnected()) {
		return;
	}
  airSensorNode.setProperty("temperature").send(String(air_sensor.getAirTemp()));
}
