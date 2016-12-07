#include "Arduino.h"
#include <ESP8266WiFi.h>
#include <Homie.h>
#include <constants.h>
#include <Timelib.h>
#include <GrowSettings.hpp>

class GrowLight
{
	public:
		void setup();
    void loop(GrowSettings grow_settings);
    GrowLight();

  private:
    HomieNode growLightNode;
    bool growLightOn;
};
