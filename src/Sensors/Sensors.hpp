#pragma once

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <Homie.h>
#include <constants.h>
#include "Sensors/AirSensor.hpp"

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

		AirSensor air_sensor;
};

extern SensorsClass Sensors;
