// Central starting point for all Grow subsystems.
#include <GrowSettings.hpp>

// Constructor - creates a GrowSettings
// and initializes the member variables and state
GrowSettings::GrowSettings():
h_aborted("aborted", "True = stop growing"),
h_start_at("start_at", "Seconds from UNIX epoch when the grow was started."),
h_settings_id("settings_id", "UUID of this setting"),
h_air_temp_high("air_temp_high", "Maximum air temp"),
h_water_temp_high("water_temp_high", "Maximum water temp"),
h_light_on_at("light_on_at", "light turns on at"),
h_light_off_at("light_off_at", "light turns off at")
{
}


void GrowSettings::setup() {
  aborted = h_aborted.get();
  start_at = h_start_at.get();
  settings_id = h_settings_id.get();
  air_temp_high = h_air_temp_high.get();
  water_temp_high = h_water_temp_high.get();
  light_on_at = h_light_on_at.get();
  light_off_at = h_light_off_at.get();
}

bool GrowSettings::get_aborted() {
  return aborted;
}

long GrowSettings::get_start_at() {
  return start_at;
}

const char* GrowSettings::get_settings_id() {
  return settings_id;
}

int GrowSettings::get_air_temp_high() {
  return air_temp_high;
}

int GrowSettings::get_water_temp_high() {
  return water_temp_high;
}

int GrowSettings::get_light_on_at() {
  return light_on_at;
}

int GrowSettings::get_light_off_at() {
  return light_off_at;
}
