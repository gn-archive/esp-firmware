#include <Arduino.h>
#include <Timelib.h>
#include <ArduinoJson.h>

#include "GrowProgram/GrowLight.hpp"
// #include "GrowProgram/ExhaustFan.hpp"
// #include "GrowProgram/AirPump.hpp"
#include "GrowProgram/WaterPump.hpp"

#include "System/Settings.hpp"

class GrowProgram
{
public:
	GrowProgram();
	void setup();
	void loop();
	void uploadCurrentState();

private:
		GrowLight grow_light;
		// ExhaustFan exhaust_fan;
		// AirPump air_pump;
		WaterPump water_pump;


};
