#include "GrowProgram/GrowErrors.hpp"

GrowErrors::GrowErrors() :
_growErrorsNode("grow_errors", "grow errors")
{
  _last_state_uplodad = 0;
  _growErrorsNode.advertise("overheat");
  _growErrorsNode.advertise("water_level_low");

  overheat = false;
  water_level_low = false;
}

void GrowErrors::loop() {
  // bool old_overheat = overheat;
  // bool old_water_level_low = water_level_low;
  // overheat = Sensors.air_sensor.getTemp() > AIR_TEMP_OVERHEAT;
  // water_level_low = Sensors.water_level.getGallons() < 1.4;



  // if (old_overheat == overheat && old_water_level_low == water_level_low) {
  //   //Return if nothing changed
  //   return;
  // }
  // uploadCurrentState();
}


void GrowErrors::uploadCurrentState() {
  // if (!Homie.isConnected()) {
  //   return;
  // }
  //
  // _growErrorsNode.setProperty("overheat").send(overheat ? "true" : "false");
  // _growErrorsNode.setProperty("water_level_low").send(water_level_low ? "true" : "false");
  //
  // if (overheat) {
  //   Notifier.send("Environment is too hot!");
  // }
  //
  // if (water_level_low) {
  //   Notifier.send("Water level low!");
  // }
}
