#include "Arduino.h"
#include <ComBus.hpp>
#include <Homie.h>

#include <constants.h>
#include <Timelib.h>
#include <GrowSettings.hpp>
#include <SensorManager.hpp>
#include <GrowErrors.hpp>

class GrowLight
{
	public:
		enum State {
			ON,
			OFF,
			OVERHEAT,
			DISABLED
		};
		GrowLight();
		void setup();
		void loop(GrowErrors grow_errors);
		void setState(State state);
		void sendCurrentState();
  private:
		State _state;
    HomieNode _growLightNode;
};
