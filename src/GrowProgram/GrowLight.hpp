#include <Arduino.h>
#include <Homie.h>

#include <constants.h>
#include <Timelib.h>
#include "eShiftReg.hpp"
#include "System/System.hpp"
#include "GrowProgram/GrowErrors.hpp"

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
		bool _power_state;
		bool _is_initialized;
		void setState(bool set_on, const char* message);
    HomieNode _growLightNode;
};
