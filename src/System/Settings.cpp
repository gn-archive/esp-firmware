#include "System/Settings.hpp"

// Constructor - creates a Settings
// and initializes the member variables and state
Settings::Settings():
h_dark_hours("dark_hours", "comma seperated hours") // comma seperated dark hours. MUST HAVE TRAILING COMMA ex. 13,14,15,16,
// h_timezone_id("timezone_id", "Time zone ex. America/Los_Angeles")
{
  // timezone_id = DEFAULT_TIMEZONE_ID;
}

void Settings::setup() {
  const char* haystack;
  if (Homie.isConfigured()) {
    haystack = h_dark_hours.get();
  } else {
    haystack = DEFAULT_DARK_HOURS;
  }

  // if the hour is present in the dark hours string (haystack),
  // flag the hour (ith element in the dark_hours array) in dark_hours as true;
  for (uint8_t i = 0; i < sizeof(dark_hours); i++) {
    // i represents the hour
    dark_hours[i] = false;

    // convert hour (i) to string
    char buffer[3]; // xx,
    if (i < 10) {
      sprintf(buffer,"0%d,", i);
    } else {
      sprintf(buffer,"%d,", i);
    }

    if(strstr(haystack, buffer)) {
      // String found, which means
      // The hour (i) is maked as dark
      dark_hours[i] = true;
    }
  }

}


bool Settings::is_light_on_at(int hour) {
  return !dark_hours[hour];
}

// const char* Settings::get_timezone_id() {
//   return timezone_id;
// }
