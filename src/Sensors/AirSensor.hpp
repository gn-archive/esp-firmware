#include <Homie.h>
#include <Wire.h>
#include <constants.h>

class AirSensor {
  private:
    AirSensorData air_sensor_data;
    void byte_to_struct_2(byte *a);
  public:
    AirSensor();
    void loop();
    float getTemp();
    float getHumidity();
};
