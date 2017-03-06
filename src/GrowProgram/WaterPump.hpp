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
    HomieNode _waterPumpNode;
    bool _power_state;
		unsigned long _power_state_changed_at;
		void setState(bool set_on);
};
