#include "Arduino.h"
#include <Homie.h>
#include <ESP8266WiFi.h>

class HomieManager
{
	private:
		HomieNode temperatureNode;
		HomieSetting<long> percentageSetting;  // id, description
		unsigned long lastSend;
  public:
    HomieManager();
    void loop();
		void setup();
};

// Constructor - creates a HomieManager
// and initializes the member variables and state
HomieManager::HomieManager() :
temperatureNode("temperature", "Fake temperature"), percentageSetting("percentage", "A simple percentage")
{
	lastSend = 0;
	percentageSetting.setDefaultValue(50).setValidator([] (long candidate) {
		Serial << "Verifying: " << candidate << endl;
		return (candidate >= 0) && (candidate <= 100);
	});
}

void HomieManager::setup() {
  Serial << "HomieManager: Setup" << endl;
}

void HomieManager::loop() {
		if (millis() - lastSend > 2000) {
			lastSend = millis();
			// send every 2000ns
			if (percentageSetting.wasProvided()) {
				Serial << "Percent :" << percentageSetting.get() << endl;
			} else {
				Serial << "Percent not provided!" << endl;
			}
		}
}
