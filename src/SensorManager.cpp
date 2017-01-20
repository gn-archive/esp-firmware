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

void SensorManagerClass::handle_incoming(String payload) {
  if (strncmp(payload.c_str(), "air_temp_f=", 11) == 0) {
    payload.remove(0, 11);
    update_air_temp_f(payload.toFloat());
  }

  if (strncmp(payload.c_str(), "water_level=", 11) == 0) {
    payload.remove(0, 11);
    update_water_level(payload.toFloat());
  }
}


void SensorManagerClass::update_air_temp_f(float new_air_temp_f) {
    air_temp_f = new_air_temp_f;

    Homie.getLogger() << F("Temperature: ") << air_temp_f << F(" °F") << endl;
    if (Homie.isConnected()) {
      airTempNode.setProperty("degrees").send(String(air_temp_f));
    }
}


void SensorManagerClass::update_water_level(float new_water_level) {
  water_level = new_water_level;
  if (Homie.isConnected()) {
    waterLevelNode.setProperty("gallons").send(String(water_level));
  }
}
