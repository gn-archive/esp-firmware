#include "GrowProgram/public/SensorManager.hpp"

SensorManager::SensorManager() :
waterLevelNode("water_level", "gallons"),
airSensorNode("air_sensor", "temperature F and RH"),
waterTempNode("water_temp", "degrees F")
{
  water_level = 0.0;
  water_temp = 0.0;
  air_temp = 0.0;
}

void SensorManager::setup() {
  airSensorNode.advertise("temperature");
  airSensorNode.advertise("humidity");
  waterLevelNode.advertise("gallons");
  waterTempNode.advertise("degrees");
}

void SensorManager::loop() {
  // Sensor readings are requested by MCUBus in main.cpp
}


float SensorManager::getAirTemp() {
  return air_temp;
}

float SensorManager::getWaterLevel() {
  return water_level;
}

void SensorManager::handle_incoming(const char* payload) {
  if (strncmp(payload, "air_temp=", 9) == 0) {
    const char * payload_trimmed = payload + 9;
    update_local_air_temp(atof(payload_trimmed));
  }

  if (strncmp(payload, "air_humidity=", 13) == 0) {
    const char * payload_trimmed = payload + 13;
    update_local_air_humidity(atof(payload_trimmed));
  }

  if (strncmp(payload, "water_temp=", 11) == 0) {
    const char * payload_trimmed = payload + 11;
    update_local_water_temp(atof(payload_trimmed));
  }

  if (strncmp(payload, "water_level=", 12) == 0) {
    const char * payload_trimmed = payload + 12;
    update_local_water_level(atof(payload_trimmed));
  }
}


void SensorManager::update_local_air_temp(float new_air_temp) {
    air_temp = new_air_temp;

    Homie.getLogger() << F("Air Temperature: ") << air_temp << F(" °F") << endl;
    if (Homie.isConnected()) {
      airSensorNode.setProperty("temperature").send(String(air_temp));
    }
}

void SensorManager::update_local_air_humidity(float new_air_humidity) {
    air_humidity = new_air_humidity;

    Homie.getLogger() << F("Air Humidity: ") << air_humidity << F(" % RH") << endl;
    if (Homie.isConnected()) {
      airSensorNode.setProperty("humidity").send(String(air_humidity));
    }
}


void SensorManager::update_local_water_temp(float new_water_temp) {
  water_temp = new_water_temp;
  Homie.getLogger() << F("Water temp: ") << water_temp << F(" °F") << endl;

  if (Homie.isConnected()) {
    waterLevelNode.setProperty("degrees").send(String(water_temp));
  }
}

void SensorManager::update_local_water_level(float new_water_level) {
  water_level = new_water_level;
  Homie.getLogger() << F("Water level: ") << water_level << F(" gallons") << endl;

  if (Homie.isConnected()) {
    waterLevelNode.setProperty("gallons").send(String(water_level));
  }
}
