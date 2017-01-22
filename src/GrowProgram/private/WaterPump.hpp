#include <Arduino.h>
#include <MCUBus.h>
#include <ESP8266WiFi.h>
#include <Homie.h>
#include <constants.h>
#include <TimeLib.h>

#define WATER_PUMP_ON_DURATION_MS 15 * 60*1000
#define WATER_PUMP_OFF_DURATION_MS 10 * 60*1000

// #define WATER_PUMP_ON_DURATION_MS 5000
// #define WATER_PUMP_OFF_DURATION_MS 1000

class WaterPump
{
	public:
		void setup();
    void loop();
    WaterPump();
		void uploadCurrentState();

  private:
    HomieNode waterPumpNode;
    bool waterPumpOn;
		unsigned long waterPumpOnChangedAt;
		void setState(bool set_on);
};
