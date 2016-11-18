// Central starting point for all Grow subsystems.
#include <GrowManager.hpp>


// Constructor - creates a GrowManager
// and initializes the member variables and state
GrowManager::GrowManager() :
grow_plan()
{
}

void GrowManager::setup() {
  Serial << "GrowManager: Initializing" << endl;

}

void GrowManager::loop() {
  if (millis() % 5000 == 0) {
    Serial << grow_plan.read() << endl;
  }
}
