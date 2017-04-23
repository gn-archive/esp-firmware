#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <Homie.h>
#include <Wire.h>
#include <constants.h>
#include <TimeLib.h>
#include "Sensors/Sensors.hpp"

class WaterPump
{
	public:
		void setup();
    void loop();
    WaterPump();
		void uploadCurrentState();

  private:
    HomieNode _waterPumpNode;
		HomieNode _waterPumpOverrideNode;
		bool _overrideEnabled;
    bool _power_state;
		void setState(bool set_on);
};
