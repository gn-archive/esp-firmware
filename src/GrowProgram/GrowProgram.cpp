// Central starting point for all Grow subsystems.
#include "GrowProgram/GrowProgram.hpp"

// Constructor - creates a GrowProgram
// and initializes the member variables and state
GrowProgram::GrowProgram() :
grow_errors(), grow_light(), exhaust_fan(), air_pump(), water_pump()
{
}

void GrowProgram::setup() {
  Homie.getLogger() << F("GrowProgram::setup()") << endl;
  setState(RUNNING);

  GrowSettings.setup();
  SensorManager.setup();
  grow_light.setup();
  exhaust_fan.setup();
  air_pump.setup();
  water_pump.setup();
}

void GrowProgram::uploadCurrentState() {
  grow_errors.uploadCurrentState();

  grow_light.uploadCurrentState();
  exhaust_fan.uploadCurrentState();
  air_pump.uploadCurrentState();
  water_pump.uploadCurrentState();
}

void GrowProgram::loop() {
  if (_state != RUNNING) {
    return;
  }

  SensorManager.loop();
  grow_errors.loop();

  grow_light.loop(grow_errors);
  exhaust_fan.loop();
}


void GrowProgram::setState(State state) {
  if (state == _state) {
    return;
  }

  _state = state;

  switch (_state) {
    case STOPPED:
      Homie.getLogger() << F("Time: ") << second() << F(" Grow Program is stopped.") << endl;
      grow_light.setState(GrowLight::DISABLED);
    break;

    case RUNNING:
      Homie.getLogger() << F("Time: ") << second() << F(" Grow Program is running.") << endl;
      grow_light.setState(GrowLight::OFF);  // Any state other than DISABLED will work
    break;
  }
}
