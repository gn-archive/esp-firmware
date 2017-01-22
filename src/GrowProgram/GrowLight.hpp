#include <Arduino.h>
#include "MCUBus.h"
#include <Homie.h>

#include <constants.h>
#include <Timelib.h>
#include "GrowSettings.hpp"
#include "GrowProgram/GrowErrors.hpp"
#include "MCUBus.h"
class GrowLight
{
	public:
		GrowLight();
		void setup();
		void loop(GrowErrors grow_errors);
		void uploadCurrentState();
		void start();
		void stop();
  private:
		bool is_on;
		bool is_running;
		void setState(bool set_on, const char* message);
    HomieNode _growLightNode;
};
