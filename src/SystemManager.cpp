#include <SystemManager.hpp>

// Constructor - creates a SystemManager
// and initializes the member variables and state
SystemManager::SystemManager() :
ntp_manager(), grow_manager()
{
}

void SystemManager::setup() {
	Serial << endl << endl << "=== SystemManager Initialization ===" << endl;

	ntp_manager.setup();
	grow_manager.setup();

	Serial << "=== SystemManager Initialization Complete ===" << endl << endl;
}

void SystemManager::loop() {
	ntp_manager.loop();
	grow_manager.loop();
}
