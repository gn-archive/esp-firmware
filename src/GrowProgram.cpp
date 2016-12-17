// Central starting point for all Grow subsystems.
#include <GrowProgram.hpp>

// Constructor - creates a GrowProgram
// and initializes the member variables and state
GrowProgram::GrowProgram() :
grow_light(), exhaust_fan(), air_pump(), water_pump()
{
}

void GrowProgram::setup() {
  Serial << "GrowProgram::setup()" << endl;
  GrowSettings.setup();
  SensorManager.setup();
  grow_light.setup();
  exhaust_fan.setup();
  air_pump.setup();
  water_pump.setup();
}

void GrowProgram::loop() {
  SensorManager.loop();

  if (GrowSettings.get_aborted()) {
    return;
  }

  grow_light.loop();
  exhaust_fan.loop();
}
