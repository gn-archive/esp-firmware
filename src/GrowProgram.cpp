// Central starting point for all Grow subsystems.
#include <GrowProgram.hpp>

// Constructor - creates a GrowProgram
// and initializes the member variables and state
GrowProgram::GrowProgram() :
grow_light(), exhaust_fan(), air_pump(), water_pump()
{
  _state = STOPPED;
}

void GrowProgram::setup() {
  Serial << "GrowProgram::setup()" << endl;
  setState(RUNNING);

  GrowSettings.setup();
  SensorManager.setup();
  grow_light.setup();
  exhaust_fan.setup();
  air_pump.setup();
  water_pump.setup();
}

void GrowProgram::loop() {
  if (_state != RUNNING) {
    return;
  }

  SensorManager.loop();

  grow_light.loop();
  exhaust_fan.loop();
}


void GrowProgram::setState(State state) {
  if (state == _state) {
    return;
  }

  _state = state;

  switch (_state) {
    case STOPPED:
      Serial << "Time: " << second() << " Grow Program is stopping." << endl;
      grow_light.setState(GrowLight::DISABLED);
    break;

    case RUNNING:
      Serial << "Time: " << second() << " Grow Program is starting." << endl;
      grow_light.setState(GrowLight::OFF);  // Any state other than DISABLED will work
    break;
  }
}
