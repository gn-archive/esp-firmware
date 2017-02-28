#pragma once

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <Homie.h>
#include <constants.h>

class SensorManager
{
	private:
		unsigned long dataLastSentAt;
		HomieNode airSensorNode;
		float air_temp;
		float air_humidity;
		void update_local_air_temp(float new_air_temp);
		void update_local_air_humidity(float new_air_temp);

		HomieNode waterTempNode;
		float water_temp;
		void update_local_water_temp(float new_water_temp);

		HomieNode waterLevelNode;
		float water_level;
		void update_local_water_level(float new_water_level);

  public:
    SensorManager();
		void setup();
    void loop();
		float getAirTemp();
		float getWaterTemp();
		float getWaterLevel();
		void handle_incoming(const char* payload);
};
