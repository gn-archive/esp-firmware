
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
		float air_temp;
		void update_local_air_temp(float new_air_temp);

		HomieNode waterTempNode;
		float water_temp;
		void update_local_water_temp(float new_water_temp);

		HomieNode waterLevelNode;
		float water_level;
		void update_local_water_level(float new_water_level);

  public:
    SensorManagerClass();
		void setup();
    void loop();
		float getAirTemp();
		float getWaterTemp();
		float getWaterLevel();
		void handle_incoming(const char* payload);
};

extern SensorManagerClass SensorManager;

#endif
