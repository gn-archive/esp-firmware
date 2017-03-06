#pragma once

#include <Arduino.h>
#include "eNotifier.hpp"
#include "Sensors/Sensors.hpp"
#include <constants.h>

class GrowErrors
{
	public:
    GrowErrors();
    void loop();

    void uploadCurrentState();

    bool overheat;
		bool water_level_low;

  private:
    HomieNode _growErrorsNode;

    unsigned long _last_state_uplodad;
};
