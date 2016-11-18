#include "Arduino.h"
#include <Homie.h>
#include <ESP8266WiFi.h>

class HomieManager
{
	private:
		HomieNode temperatureNode;
		HomieSetting<const char*> growPlan;
		unsigned long lastSend;
  public:
    HomieManager();
    void loop();
		void setup();
};

// Constructor - creates a HomieManager
// and initializes the member variables and state
HomieManager::HomieManager() :
temperatureNode("temperature", "Fake temperature"), growPlan("growplan", "JSON representation of the grow plan.")
{
	lastSend = 0;
	growPlan.setDefaultValue("").setValidator([] (const char* candidate) {
		if (candidate == NULL) {
			return false;
		}
		return true;
	});
}

void HomieManager::setup() {
  Serial << "HomieManager: Setup" << endl;
}

void HomieManager::loop() {
		if (millis() - lastSend > 2000) {
			lastSend = millis();
			// send every 2000ns
			if (growPlan.wasProvided()) {
				Serial << "Grow Plan :" << growPlan.get() << endl;
			} else {
				Serial << "Grow Plan not provided!" << endl;
			}
		}
}
