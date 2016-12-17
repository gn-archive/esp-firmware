#ifndef GROW_SETTINGS_H
#define GROW_SETTINGS_H

#pragma once

#include "Arduino.h"
#include <ESP8266WiFi.h>
#include <Homie.h>

class GrowSettingsClass
{
	private:
		// void setup();

		HomieSetting<bool> h_aborted;
		HomieSetting<const char*> h_settings_id;
		HomieSetting<long>  h_air_temp_high;
		HomieSetting<long>  h_air_temp_low;
		HomieSetting<long>  h_water_temp_high;
		HomieSetting<long>  h_water_temp_low;
		HomieSetting<long>  h_light_on_at;
		HomieSetting<long>  h_light_off_at;

		bool aborted;
		const char* settings_id;
		int air_temp_high;
		int air_temp_low;
		int water_temp_high;
		int water_temp_low;
		int light_on_at;
		int light_off_at;

	public:
    GrowSettingsClass();
		void setup();

		bool get_aborted();
		const char* get_settings_id();
		int get_air_temp_high();
		int get_air_temp_low();
		int get_water_temp_high();
		int get_water_temp_low();
		int get_light_on_at();
		int get_light_off_at();
};


extern GrowSettingsClass GrowSettings;

#endif
