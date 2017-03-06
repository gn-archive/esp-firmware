#pragma once

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <Homie.h>
#include <everytime.h>
#include <constants.h>
#include "Sensors/AirSensor.hpp"
#include "Sensors/WaterTempSensor.hpp"

class SensorsClass
{
	private:
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
};

extern SensorsClass Sensors;
