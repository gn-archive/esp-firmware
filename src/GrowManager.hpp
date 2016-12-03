#include "Arduino.h"
#include <ESP8266WiFi.h>
#include <Timelib.h>
#include <Homie.h>
#include <ArduinoJson.h>

class GrowManager
{
	private:
		HomieSetting<const char*> h_plant_stages_json;
		HomieSetting<long> h_grow_start_at;
		HomieSetting<bool> h_grow_aborted;
		const char* plant_stages_json;
		long grow_start_at;
		bool grow_aborted;

		// Refactor these
		HomieNode growLightNode;
		bool growLightOn;
  public:
    GrowManager();
    void loop(float air_temp_f);
		void setup();
};
