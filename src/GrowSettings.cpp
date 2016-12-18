#include <GrowSettings.hpp>

// Constructor - creates a GrowSettingsClass
// and initializes the member variables and state
GrowSettingsClass::GrowSettingsClass():
h_aborted("aborted", "True = stop growing"),
h_settings_id("settings_id", "UUID of this setting"),
h_light_on_at("light_on_at", "light turns on at"),
h_light_off_at("light_off_at", "light turns off at")
{
}

GrowSettingsClass GrowSettings;


void GrowSettingsClass::setup() {
  aborted = h_aborted.get();
  settings_id = h_settings_id.get();
  light_on_at = h_light_on_at.get();
  light_off_at = h_light_off_at.get();
}

bool GrowSettingsClass::get_aborted() {
  return aborted;
}

const char* GrowSettingsClass::get_settings_id() {
  return settings_id;
}

int GrowSettingsClass::get_light_on_at() {
  return light_on_at;
}

int GrowSettingsClass::get_light_off_at() {
  return light_off_at;
}
