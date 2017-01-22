#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <Homie.h>
#include <constants.h>
#include <Timelib.h>
#include "GrowSettings.hpp"

class ExhaustFan
{
	public:
		void setup();
    void loop();
    ExhaustFan();
		void uploadCurrentState();
  private:
		HomieNode fanNode;
		void ensureOn(bool yes);
		bool fanOn;
};
