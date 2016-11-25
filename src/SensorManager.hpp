#include "Arduino.h"
#include <ESP8266WiFi.h>
#include <Homie.h>

class SensorManager
{
	private:
		unsigned long dataLastSentAt;
		HomieNode temperatureNode;
  public:
    SensorManager();
    void loop();
		void setup();
};
