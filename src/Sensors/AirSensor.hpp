#include <Homie.h>
#include <dht.h>
#include <constants.h>
#include <RunningMedian.h>

class AirSensor {
  private:
    dht _air_sensor;
    RunningMedian _air_temp;
    RunningMedian _air_humidity;
    unsigned long air_sensor_last_read;
  public:
    AirSensor();
    void loop();
    float getTemp();
    float getHumidity();

  private:
    void readSensor();
};
