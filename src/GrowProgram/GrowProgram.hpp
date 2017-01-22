#include <Arduino.h>
#include <Timelib.h>
#include <ArduinoJson.h>

#include "GrowProgram/private/GrowLight.hpp"
#include "GrowProgram/private/ExhaustFan.hpp"
#include "GrowProgram/private/AirPump.hpp"
#include "GrowProgram/private/WaterPump.hpp"

#include "System/public/Settings.hpp"
#include "GrowProgram/private/GrowErrors.hpp"

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

	SensorManager sensors;

private:
		State _state;
		GrowErrors grow_errors;
		GrowLight grow_light;
		ExhaustFan exhaust_fan;
		AirPump air_pump;
		WaterPump water_pump;


};
