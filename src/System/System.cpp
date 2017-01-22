#include "System/System.hpp"

SystemClass::SystemClass():
time_manager()
{
}
// Initialize System global/extern
SystemClass System;


void SystemClass::setup() {
  settings.setup();
  time_manager.setup();
}


void SystemClass::loop() {
  time_manager.loop();
}
