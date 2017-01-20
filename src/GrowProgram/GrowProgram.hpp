#include <Arduino.h>
#include <Timelib.h>
#include <ArduinoJson.h>

#include "GrowLight.hpp"
#include "ExhaustFan.hpp"
#include "AirPump.hpp"
#include "WaterPump.hpp"

#include "GrowSettings.hpp"
#include "GrowErrors.hpp"

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
	void uploadCurrentState();
private:
		State _state;
		GrowErrors grow_errors;
		GrowLight grow_light;
		ExhaustFan exhaust_fan;
		AirPump air_pump;
		WaterPump water_pump;


};
