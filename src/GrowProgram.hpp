#include "Arduino.h"
#include <ESP8266WiFi.h>
#include <Timelib.h>
#include <Homie.h>
#include <ArduinoJson.h>

#include <GrowSettings.hpp>

#include <GrowLight.hpp>
#include <ExhaustFan.hpp>
#include <AirPump.hpp>
#include <WaterPump.hpp>


class GrowProgram
{
public:
	enum State {
		STOPPED,
		RUNNING
	};
	GrowProgram();
	void setup();
	void loop();
	void setState(State state);
	void sendCurrentState();
private:
		State _state;

		GrowLight grow_light;
		ExhaustFan exhaust_fan;
		AirPump air_pump;
		WaterPump water_pump;


};
