
#ifndef SENSOR_MANAGER_H
#define SENSOR_MANAGER_H

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <Homie.h>
#include <constants.h>
#include "GrowSettings.hpp"

class SensorManagerClass
{
	private:
		unsigned long dataLastSentAt;
		HomieNode airTempNode;
		float air_temp_f;
		void update_air_temp_f(float new_air_temp_f);

		HomieNode waterLevelNode;
		float water_level;
		void update_water_level(float new_water_level);

  public:
    SensorManagerClass();
		void setup();
    void loop();
		float getAirTempF();
		float getWaterLevel();
		void handle_incoming(const char* payload);
};

extern SensorManagerClass SensorManager;

#endif
