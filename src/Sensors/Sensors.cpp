#include "Sensors/Sensors.hpp"

SensorsClass::SensorsClass():
waterLevelNode("water_level", "gallons"),
airSensorNode("air_sensor", "temperature F and RH"),
waterTempNode("water_temp", "degrees F"),
air_sensor(),
water_temp_sensor()
{

}
SensorsClass Sensors;

void SensorsClass::setup() {
  airSensorNode.advertise("temperature");
  airSensorNode.advertise("humidity");
  waterLevelNode.advertise("gallons");
  waterTempNode.advertise("temperature");

  water_temp_sensor.setup();
}

void SensorsClass::loop() {
  air_sensor.loop();
  water_temp_sensor.loop();

  every(SEND_SENSOR_DATA_INTERVAL) {
    uploadCurrentState();
  }
}


void SensorsClass::uploadCurrentState() {
  Homie.getLogger()
  << "Air temperature: "
  << air_sensor.getTemp()
  << " °F, humidity: "
  << air_sensor.getHumidity()
  << "% RH"
  << endl
  << "Water temperature: "
  << water_temp_sensor.getTemp()
  << " °F"
  << endl;

  if (!Homie.isConnected()) {
		return;
	}
  airSensorNode.setProperty("temperature").send(String(air_sensor.getTemp()));
  airSensorNode.setProperty("humidity").send(String(air_sensor.getHumidity()));
  waterTempNode.setProperty("temperature").send(String(water_temp_sensor.getTemp()));

}
