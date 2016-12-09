#include "Arduino.h"
#include <ESP8266WiFi.h>
#include <Homie.h>
#include <constants.h>
#include <GrowSettings.hpp>
#include <SensorManager.hpp>

class WaterPump
{
	public:
		void setup();
    void loop(GrowSettings grow_settings, SensorManager sensors);
    WaterPump();

  private:
    HomieNode waterPumpNode;
		void ensureOn(bool yes);
    bool waterPumpOn;
};
