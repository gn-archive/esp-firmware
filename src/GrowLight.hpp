#include "Arduino.h"
#include <ESP8266WiFi.h>
#include <Homie.h>
#include <constants.h>
#include <Timelib.h>
#include <GrowSettings.hpp>
#include <SensorManager.hpp>

class GrowLight
{
	public:
		void setup();
		void loop();
    GrowLight();

  private:
    HomieNode growLightNode;
		void ensureOn(bool yes);
    bool growLightOn;
};
