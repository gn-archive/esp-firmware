#include "Arduino.h"
#include <ESP8266WiFi.h>
#include <Homie.h>
#include <constants.h>
#include <Timelib.h>
#include <GrowSettings.hpp>
#include <SensorManager.hpp>
class ExhaustFan
{
	public:
		void setup();
    void loop(GrowSettings grow_settings, SensorManager sensors);
    ExhaustFan();

  private:
		HomieNode fanNode;

		bool fanOn;
};
