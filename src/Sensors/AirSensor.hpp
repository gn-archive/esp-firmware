#include <Homie.h>
#include <DHT.h>
#include <everytime.h>
#include <constants.h>
#include <RunningMedian.h>

class AirSensor {
  private:
    DHT _air_sensor;
    RunningMedian _air_temp;
    RunningMedian _air_humidity;
  public:
    AirSensor();
    void loop();
    float getTemp();
    float getHumidity();

  private:
    void readSensor();
};
