#include <SystemManager.hpp>

// Constructor - creates a SystemManager
// and initializes the member variables and state
SystemManager::SystemManager() :
grow_manager()
{
}

void SystemManager::setup() {
	Serial << "SystemManager: Initializing" << endl;
	grow_manager.setup();
}

void SystemManager::loop() {
	grow_manager.loop();
}
