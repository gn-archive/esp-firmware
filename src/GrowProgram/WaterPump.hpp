#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <Homie.h>
#include <constants.h>

class WaterPump
{
	public:
		void setup();
    void loop();
    WaterPump();
		void sendCurrentState();

  private:
    HomieNode waterPumpNode;
    bool waterPumpOn;
};