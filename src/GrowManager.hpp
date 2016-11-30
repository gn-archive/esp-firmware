#include "Arduino.h"
#include <ESP8266WiFi.h>
#include <Timelib.h>
#include <Homie.h>
#include <ArduinoJson.h>

class GrowManager
{
	private:
		HomieSetting<const char*> plant_stages_json;
		HomieSetting<long> grow_start_at;
		HomieSetting<bool> grow_aborted;
  public:
    GrowManager();
    void loop();
		void setup();
};
