#include "Sensors/Sensors.hpp"

SensorsClass::SensorsClass():
waterLevelNode("water_level", "gallons"),
airSensorNode("air_sensor", "temperature F and RH"),
waterTempNode("water_temp", "degrees F"),
air_sensor()
{
  dataLastSentAt = 0;
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

  if (millis() - dataLastSentAt > SEND_SENSOR_DATA_INTERVAL) {
    dataLastSentAt = millis();
    uploadCurrentState();
  }
}


void SensorsClass::uploadCurrentState() {
  Homie.getLogger()
  << "Temperature: "
  << air_sensor.getTemp()
  << " °F, Humidity: "
  << air_sensor.getHumidity()
  << "% RH"
  << endl;

  if (!Homie.isConnected()) {
		return;
	}
  airSensorNode.setProperty("temperature").send(String(air_sensor.getTemp()));
  airSensorNode.setProperty("humidity").send(String(air_sensor.getHumidity()));

}
