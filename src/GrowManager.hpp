#include "Arduino.h"
#include <ESP8266WiFi.h>

#include <GrowPlan.hpp>

class GrowManager
{
	private:
		GrowPlan grow_plan;
  public:
    GrowManager();
    void loop();
		void setup();
};
