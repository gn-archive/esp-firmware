#include "Arduino.h"
#include <Homie.h>
#include <ESP8266WiFi.h>

class SystemManager
{
	private:
		HomieNode temperatureNode;
		HomieSetting<const char*> growPlan;
		unsigned long lastSend;
  public:
    SystemManager();
    void loop();
		void setup();
};
