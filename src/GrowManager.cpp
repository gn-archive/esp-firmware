// Central starting point for all Grow subsystems.
#include <GrowManager.hpp>


// Constructor - creates a GrowManager
// and initializes the member variables and state
GrowManager::GrowManager() :
grow_plan()
{
}

void GrowManager::setup() {
  Serial << "GrowManager..." << endl;
  grow_plan.setup();
}

void GrowManager::loop() {
}
