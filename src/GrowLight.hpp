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
		enum State {
			ON,
			OFF,
			OVERHEAT,
			ERROR
		};
		void setup();
		void loop();
    GrowLight();

  private:
		State _state;
    HomieNode growLightNode;
		void setState(State state);
};
