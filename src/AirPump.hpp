#include "Arduino.h"
#include <ESP8266WiFi.h>
#include <Homie.h>
#include <constants.h>

class AirPump
{
	public:
		void setup();
    AirPump();
		void sendCurrentState();
  private:
    HomieNode airPumpNode;
    bool airPumpOn;
};
