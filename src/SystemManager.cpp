#include <SystemManager.hpp>

// Constructor - creates a SystemManager
// and initializes the member variables and state
SystemManager::SystemManager() :
grow_manager()
{
}

void SystemManager::setup() {
	Serial << endl << endl << "=== SystemManager Initialization ===" << endl;
	grow_manager.setup();
	Serial << "=== SystemManager Initialization Complete ===" << endl << endl;
}

void SystemManager::loop() {
	grow_manager.loop();
}
