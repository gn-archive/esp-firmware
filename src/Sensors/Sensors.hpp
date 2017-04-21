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

  public:
    SensorsClass();
		void setup();
    void loop();
		void uploadCurrentState();

		AirSensor air_sensor;
};

extern SensorsClass Sensors;
