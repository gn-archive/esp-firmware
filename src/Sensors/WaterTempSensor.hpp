#include <Homie.h>
#include <everytime.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <constants.h>

class WaterTempSensor {
  private:
    OneWire bus;
    DallasTemperature sensors;
    float temperature;

  public:
    WaterTempSensor();
    void setup();
    void loop();
    float getTemp();

  private:
    void readSensor();
};
