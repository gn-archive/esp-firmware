#include "Arduino.h"
#include <ESP8266WiFi.h>
#include <Homie.h>
#include <DHT.h>

class SensorManager
{
	private:
		unsigned long dataLastSentAt;
		HomieNode airTempNode;
		DHT air_temp_sensor;
		float air_temp_f;
  public:
    SensorManager();
		void setup();
    void loop();
		float getAirTempF();
};
