#include "Arduino.h"
#include <Notifier.hpp>
#include <SensorManager.hpp>
#include <constants.h>
class GrowErrors
{
	public:
    GrowErrors();
    void loop();

    void sendCurrentState();


  private:
    bool _overheating;
    unsigned long _overheated_at;
    void setOverheat(bool overheating);

    bool _water_level_low;
    void setWaterLevelLow(bool water_level_low);
};
