#include <Homie.h>
#include <constants.h>

class AirSensor {
  private:
    unsigned long air_sensor_last_read;
    float _temperature;
    float _humidity;
  public:
    AirSensor();
    void loop();
    float getTemp();
    float getHumidity();
};
