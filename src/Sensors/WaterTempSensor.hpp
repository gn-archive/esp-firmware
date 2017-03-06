#include <Homie.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <constants.h>
#include <RunningMedian.h>

class WaterTempSensor {
  private:
    OneWire _bus;
    DallasTemperature _temp_sensors;
    RunningMedian _temperature;
    unsigned long last_read;
    void readSensor();

  public:
    WaterTempSensor();
    void setup();
    void loop();
    float getTemp();
};
