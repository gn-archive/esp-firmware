#include <Homie.h>
#include <constants.h>
#include <Adafruit_ADS1015.h>
#include <Wire.h>

class WaterLevelSensor {
  private:
    Adafruit_ADS1115 ads;
    int16_t _water_level;
    unsigned long _last_read;
  public:
    WaterLevelSensor();
    void setup();
    void loop();
    int16_t getWaterLevel();
    bool waterLevelLow();
};
