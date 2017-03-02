#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <Homie.h>
#include <constants.h>
#include <TimeLib.h>
#include "eShiftReg.hpp"

class WaterPump
{
	public:
		void setup();
    void loop();
    WaterPump();
		void uploadCurrentState();

  private:
    HomieNode waterPumpNode;
    bool waterPumpOn;
		unsigned long waterPumpOnChangedAt;
		void setState(bool set_on);
};
