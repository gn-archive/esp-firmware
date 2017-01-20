#include "SensorManager.hpp"

SensorManagerClass::SensorManagerClass() :
waterLevelNode("waterlevel", "gallons"),
airTempNode("temperature", "degrees F")
{
  water_level = 0.0;
  air_temp_f = 0.0;
}

SensorManagerClass SensorManager;

void SensorManagerClass::setup() {
  airTempNode.advertise("degrees");
  waterLevelNode.advertise("gallons");
}

void SensorManagerClass::loop() {
  // Sensor readings are requested by MCUBus in main.cpp
}


float SensorManagerClass::getAirTempF() {
  return air_temp_f;
}

float SensorManagerClass::getWaterLevel() {
  return water_level;
}

void SensorManagerClass::handle_incoming(const char* payload) {
  if (strncmp(payload, "air_temp_f=", 11) == 0) {
    const char * payload_trimmed = payload + 11;
    update_local_air_temp_f(atof(payload_trimmed));
  }

  if (strncmp(payload, "water_level=", 12) == 0) {
    const char * payload_trimmed = payload + 12;
    update_local_water_level(atof(payload_trimmed));
  }
}


void SensorManagerClass::update_local_air_temp_f(float new_air_temp_f) {
    air_temp_f = new_air_temp_f;

    Homie.getLogger() << F("Temperature: ") << air_temp_f << F(" °F") << endl;
    if (Homie.isConnected()) {
      airTempNode.setProperty("degrees").send(String(air_temp_f));
    }
}


void SensorManagerClass::update_local_water_level(float new_water_level) {
  water_level = new_water_level;
  Homie.getLogger() << F("Water level: ") << water_level << F(" gallons") << endl;

  if (Homie.isConnected()) {
    waterLevelNode.setProperty("gallons").send(String(water_level));
  }
}
