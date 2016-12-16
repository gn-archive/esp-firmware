#include <SensorManager.hpp>

SensorManager::SensorManager() :
airTempNode("temperature", "temperature"),
air_temp_sensor(AIR_SENSOR_DHT_PIN, AIR_SENSOR_DHT)
{
  dataLastSentAt = 0;
}

void SensorManager::setup() {
  airTempNode.advertise("degrees");
}

void SensorManager::loop() {
  if (millis() - dataLastSentAt >= SEND_STATS_INTERVAL || dataLastSentAt == 0) {
    dataLastSentAt = millis();
    float new_air_temp_f = air_temp_sensor.readTemperature(true);

    if (isnan(new_air_temp_f)) {
    Serial.println("Failed to read air_temp_sensor!");
      return;
    }
    air_temp_f = new_air_temp_f;

    Serial << "Temperature: " << air_temp_f << " °F" << endl;
    airTempNode.setProperty("degrees").send(String(air_temp_f));
  }

  bool is_overheating = air_temp_f > 70;
  Notifier.setOverheat(is_overheating);
}


float SensorManager::getAirTempF() {
  return air_temp_f;
}
