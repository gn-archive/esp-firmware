#include <Homie.h>
#include <Wire.h>
#include <constants.h>

class AirSensor {
  private:
    AirSensorData air_sensor_data;
    unsigned long last_request;
    bool last_request_success;
    void byte_to_struct_2(byte *a);
  public:
    AirSensor();
    void loop();
    float getTemp();
    float getHumidity();
};
