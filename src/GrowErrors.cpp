#include <GrowErrors.hpp>

GrowErrors::GrowErrors() {
  _overheated_at = 0;
}

void GrowErrors::loop() {
  bool is_overheating = SensorManager.getAirTempF() > AIR_TEMP_OVERHEAT;
  setOverheat(is_overheating);


  if (SensorManager.getWaterLevel() < 4.5) {
    setWaterLevelLow(true);
  } else {
    setWaterLevelLow(false);
  }
}


void GrowErrors::sendCurrentState() {
  if (_overheating) {
    Notifier.send("Environment is too hot!");
  }

  if (_water_level_low) {
    Notifier.send("Water level low!");
  }
}

void GrowErrors::setOverheat(bool overheating) {
	if (_overheating == overheating && millis() - _overheated_at < 1000*60*60*6 ) {
		return;	// only notify once every 6 hours
	}

	_overheating = overheating;
	_overheated_at = 0;  // Will be zero if not overheating

	if (_overheating) {
		_overheated_at = millis();
    sendCurrentState();
	}
}

bool GrowErrors::getOverheat() {
  return _overheating;
}

void GrowErrors::setWaterLevelLow(bool water_level_low) {
	if (_water_level_low == water_level_low) {
		return;
	}

	_water_level_low = water_level_low;

  sendCurrentState();
}
