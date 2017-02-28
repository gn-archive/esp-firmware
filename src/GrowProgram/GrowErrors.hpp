#pragma once

#include <Arduino.h>
#include "eNotifier.hpp"
#include "GrowProgram/eSensorManager.hpp"
#include <constants.h>

class GrowErrors
{
	public:
    GrowErrors();
    void loop(SensorManager sensors);

    void uploadCurrentState();

    bool getOverheat();

  private:
    HomieNode growErrorsNode;

    bool _overheat;
    unsigned long _overheat_at;
    void setOverheat(bool overheat);

    bool _water_level_low;
    void setWaterLevelLow(bool water_level_low);
};