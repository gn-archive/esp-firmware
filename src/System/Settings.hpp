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
		HomieSetting<long>  h_light_off_at;
		// HomieSetting<const char*>  h_timezone_id;

		int light_on_at;
		int light_off_at;
		// const char* timezone_id;

	public:
    Settings();
		void setup();

		int get_light_on_at();
		int get_light_off_at();
		// const char* get_timezone_id();
};
