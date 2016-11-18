// Central starting point for all subsystems affected by internet.
#include <SystemManager.hpp>

// Constructor - creates a SystemManager
// and initializes the member variables and state
SystemManager::SystemManager() :
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

void SystemManager::setup() {
  Serial << "SystemManager: Setup" << endl;
}

void SystemManager::loop() {
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
