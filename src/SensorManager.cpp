#include <SensorManager.hpp>
#define SEND_INTERVAL 10*1000

#define DHTTYPE DHT11
#define DHTPIN D1

SensorManager::SensorManager() :
airTempNode("temperature", "temperature"),
air_temp_sensor(DHTPIN, DHTTYPE)
{
  dataLastSentAt = 0;
}

void SensorManager::setup() {
  airTempNode.advertise("degrees");
}

void SensorManager::loop() {

  if (millis() - dataLastSentAt >= SEND_INTERVAL || dataLastSentAt == 0) {
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
}


float SensorManager::getAirTempF() {
  return air_temp_f;
}
