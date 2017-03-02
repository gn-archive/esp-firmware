#include <Homie.h>
#include <DHT.h>
#include <constants.h>

class AirSensor {
  private:
    DHT air_sensor;
    float air_temp;
    float air_humidity;
    unsigned long air_sensor_last_read;


  public:
    AirSensor();
    void loop();
    float getTemp();
    float getHumidity();

  private:
    void readSensor();
};
