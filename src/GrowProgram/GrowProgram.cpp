#include "GrowProgram/GrowProgram.hpp"

GrowProgram::GrowProgram() :
grow_light(),
// exhaust_fan(),
// air_pump(),
water_pump(),
peltier_cooler()
{
}

void GrowProgram::setup() {
  grow_light.setup();
  // exhaust_fan.setup();
  // air_pump.setup();
  water_pump.setup();
  peltier_cooler.setup();
}

void GrowProgram::uploadCurrentState() {
  grow_light.uploadCurrentState();
  // exhaust_fan.uploadCurrentState();
  // air_pump.uploadCurrentState();
  water_pump.uploadCurrentState();
  peltier_cooler.uploadCurrentState();
}

void GrowProgram::loop() {
  grow_light.loop();
  // exhaust_fan.loop();
  water_pump.loop();
  peltier_cooler.loop();
}
