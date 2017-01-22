#include "GrowProgram/private/GrowErrors.hpp"

GrowErrors::GrowErrors() :
growErrorsNode("grow_errors", "grow errors")
{
  _overheat_at = 0;
  growErrorsNode.advertise("overheat");
  growErrorsNode.advertise("water_level_low");
}

void GrowErrors::loop(SensorManager sensors) {
  bool is_overheat = sensors.getAirTemp() > AIR_TEMP_OVERHEAT;
  setOverheat(is_overheat);


  if (sensors.getWaterLevel() < 4.5) {
    setWaterLevelLow(true);
  } else {
    setWaterLevelLow(false);
  }
}


void GrowErrors::uploadCurrentState() {
  if (!Homie.isConnected()) {
    return;
  }

  growErrorsNode.setProperty("overheat").send(_overheat ? "true" : "false");
  growErrorsNode.setProperty("water_level_low").send(_water_level_low ? "true" : "false");

  if (_overheat) {
    Notifier.send("Environment is too hot!");
  }

  if (_water_level_low) {
    Notifier.send("Water level low!");
  }
}

void GrowErrors::setOverheat(bool overheat) {
	if (_overheat == overheat && millis() - _overheat_at < 1000*60*60*6 ) {
		return;	// only notify once every 6 hours
	}

	_overheat = overheat;
	_overheat_at = 0;  // Will be zero if not overheat

  uploadCurrentState();

  if (_overheat) {
		_overheat_at = millis();
	}
}

bool GrowErrors::getOverheat() {
  return _overheat;
}

void GrowErrors::setWaterLevelLow(bool water_level_low) {
	if (_water_level_low == water_level_low) {
		return;
	}

	_water_level_low = water_level_low;

  uploadCurrentState();
}
