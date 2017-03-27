#include <Homie.h>
#include <constants.h>
#include <Wire.h>

class WaterLevelSensor {
  private:
    uint8_t _water_level;
    unsigned long _last_read;
  public:
    WaterLevelSensor();
    void loop();
    uint8_t getWaterLevel();
    bool waterLevelLow();
};
