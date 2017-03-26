#include <Homie.h>
#include <constants.h>
#include <Wire.h>

class WaterLevelSensor {
  private:
    bool _water_level_low;
    unsigned long _last_read;
  public:
    WaterLevelSensor();
    void loop();
    bool getWaterLevel();
};
