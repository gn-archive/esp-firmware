#pragma once

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <Homie.h>
#include <constants.h>
#include "Sensors/AirSensor.hpp"
#include "Sensors/WaterTempSensor.hpp"
#include "Sensors/WaterLevelSensor.hpp"

class SensorsClass
{
	private:
		unsigned long dataLastSentAt;
		HomieNode airSensorNode;
		HomieNode waterTempNode;
		HomieNode waterLevelNode;

  public:
    SensorsClass();
		void setup();
    void loop();
		void uploadCurrentState();

		AirSensor air_sensor;
		WaterTempSensor water_temp_sensor;
		WaterLevelSensor water_level_sensor;
};

extern SensorsClass Sensors;
