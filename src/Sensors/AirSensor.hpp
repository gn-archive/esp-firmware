#include <Homie.h>
#include <DHT.h>
#include <everytime.h>
#include <constants.h>

class AirSensor {
  private:
    DHT air_sensor;
    float air_temp;
    float air_humidity;

  public:
    AirSensor();
    void loop();
    float getTemp();
    float getHumidity();

  private:
    void readSensor();
};
