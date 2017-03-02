#include "System/Settings.hpp"

// Constructor - creates a Settings
// and initializes the member variables and state
Settings::Settings():
h_light_on_at("light_on_at", "light turns on at"),
h_light_off_at("light_off_at", "light turns off at")
// h_timezone_id("timezone_id", "Time zone ex. America/Los_Angeles")
{
  light_on_at = DEFAULT_GROW_LIGHT_ON_AT;
  light_off_at = DEFAULT_GROW_LIGHT_OFF_AT;
  // timezone_id = DEFAULT_TIMEZONE_ID;
}

void Settings::setup() {
  if (Homie.isConfigured()) {
    light_on_at = h_light_on_at.get() ;
    light_off_at = h_light_off_at.get();
  }
}


int Settings::get_light_on_at() {
  return light_on_at;
}

int Settings::get_light_off_at() {
  return light_off_at;
}


// const char* Settings::get_timezone_id() {
//   return timezone_id;
// }
