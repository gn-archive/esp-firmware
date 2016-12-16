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


class GrowManager
{
	private:
		bool growManagerSetupRan;
		void setup();

		GrowLight grow_light;
		ExhaustFan exhaust_fan;
		AirPump air_pump;
		WaterPump water_pump;
  public:
    GrowManager();
		void loop();
};
