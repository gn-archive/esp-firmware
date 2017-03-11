#pragma once

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <Homie.h>
#include <constants.h>

class Settings
{
	private:
		// void setup();

		HomieSetting<long>  h_light_on_at;
		HomieSetting<long>  h_light_on_duration;
		// HomieSetting<const char*>  h_timezone_id;

		// const char* timezone_id;

	public:
    Settings();
		void setup();

		int light_on_at;
		int light_on_duration;
		int get_light_on_at();
		int get_light_on_duration();
		// const char* get_timezone_id();
};
