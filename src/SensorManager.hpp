#pragma once
#ifndef SENSOR_MANAGER_H
#define SENSOR_MANAGER_H

#include "Arduino.h"
#include <ESP8266WiFi.h>
#include <Homie.h>
#include <DHT.h>
#include <constants.h>
#include <GrowSettings.hpp>
#include <Notifier.hpp>

class SensorManagerClass
{
	private:
		unsigned long dataLastSentAt;
		HomieNode airTempNode;
		DHT air_temp_sensor;
		float air_temp_f;

		HomieNode waterLevelNode;
		float water_level;
  public:
    SensorManagerClass();
		void setup();
    void loop();
		float getAirTempF();
		float getWaterLevel();
};

extern SensorManagerClass SensorManager;

#endif
