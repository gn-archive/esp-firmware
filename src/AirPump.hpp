#include "Arduino.h"
#include <ESP8266WiFi.h>
#include <Homie.h>
#include <constants.h>
#include <Timelib.h>
#include <GrowSettings.hpp>
#include <SensorManager.hpp>

class AirPump
{
	public:
		void setup();
    void loop(GrowSettings grow_settings, SensorManager sensors);
    AirPump();

  private:
    HomieNode airPumpNode;
		void ensureOn(bool yes);
    bool airPumpOn;
};
