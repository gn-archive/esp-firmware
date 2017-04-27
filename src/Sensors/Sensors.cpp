#include "Sensors/Sensors.hpp"

SensorsClass::SensorsClass():
airSensorNode("air_sensor", "temperature F and RH"),
air_sensor()
{
  dataLastSentAt = 0;
}
SensorsClass Sensors;

void SensorsClass::setup() {
  airSensorNode.advertise("temperature");
  airSensorNode.advertise("humidity");

}

void SensorsClass::loop() {
  air_sensor.loop();

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

  if (!Homie.isConnected()) {
		return;
	}
  airSensorNode.setProperty("temperature").send(String(air_sensor.getTemp()));
  airSensorNode.setProperty("humidity").send(String(air_sensor.getHumidity()));
}
