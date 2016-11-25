#include <SensorManager.hpp>
#define SEND_INTERVAL 10*1000

SensorManager::SensorManager() :
temperatureNode("temperature", "temperature")
{
  dataLastSentAt = 0;
}

void SensorManager::setup() {
  temperatureNode.advertise("degrees");
}

void SensorManager::loop() {
  // Read sensor data here. Fake temperature here, for the example
  float temperature = 22;

  if (Homie.isConnected() && (millis() - dataLastSentAt >= SEND_INTERVAL || dataLastSentAt == 0)) {
    Serial << "Temperature: " << temperature << " °C" << endl;
    temperatureNode.setProperty("degrees").send(String(temperature));
    dataLastSentAt = millis();
  }
}
