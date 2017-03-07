#include <Arduino.h>
#include <Homie.h>

#include <constants.h>
#include <Timelib.h>
#include "eShiftReg.hpp"
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
		unsigned long _last_overheat;
		bool _power_state;
		bool _is_initialized;
		void setState(bool set_on, const char* message);
    HomieNode _growLightNode;
};
