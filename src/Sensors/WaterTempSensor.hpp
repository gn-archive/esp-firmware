#include <Homie.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <constants.h>

class WaterTempSensor {
  private:
    OneWire bus;
    DallasTemperature sensors;
    float temperature;
    unsigned long last_read;


  public:
    WaterTempSensor();
    void setup();
    void loop();
    float getTemp();

  private:
    void readSensor();
};
