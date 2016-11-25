#include "Arduino.h"
#include <Homie.h>
#include <ESP8266WiFi.h>

class GrowPlan
{
	private:
		HomieSetting<const char*> grow_plan_json;
  public:
    GrowPlan();
    void loop();
		void setup();
		String read();
		bool refresh();
};
