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
			DISABLED
		};
		GrowLight();
		void setup();
		void loop();
		void setState(State state);
		void sendCurrentState();
  private:
		State _state;
    HomieNode _growLightNode;
};
