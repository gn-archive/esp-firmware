#include <Arduino.h>
#include <Homie.h>
#include <Chronos.h>

#include <constants.h>
#include <Timelib.h>
#include "Sensors/Sensors.hpp"
#include "System/System.hpp"

class GrowLight
{
	public:
		GrowLight();
		void setup();
		void loop();
		void uploadCurrentState();
		void start();
		void stop();
  private:
		bool _overrideEnabled;
		bool _overheat;
		bool _power_state;
		void setState(bool set_on, const char* message);
    HomieNode _growLightNode;
		HomieNode _growLightOverrideNode;
};
