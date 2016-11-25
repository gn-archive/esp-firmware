#include <SensorManager.hpp>
#define SEND_INTERVAL 10*1000

SensorManager::SensorManager() :
temperatureNode("temperature", "temperature")
{
  dataLastSentAt = 0;
}

void SensorManager::setup() {
  temperatureNode.advertise("unit");
  temperatureNode.advertise("degrees");
}

void SensorManager::loop() {
  if (millis() - dataLastSentAt >= SEND_INTERVAL || dataLastSentAt == 0) {
    float temperature = 22; // Fake temperature here, for the example
    Serial << "Temperature: " << temperature << " °C" << endl;
    temperatureNode.setProperty("degrees").send(String(temperature));
    dataLastSentAt = millis();
  }
}
