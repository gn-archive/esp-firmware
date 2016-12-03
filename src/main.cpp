#include "Arduino.h"

#include <Homie.h>
#include <NtpManager.hpp>
#include <GrowManager.hpp>
#include <SensorManager.hpp>
// #include <Led.cpp>
// D0 = NodeMCU LED
// D4 = ESP8266 LED

// Led test_led(D0);

NtpManager ntp_manager;
GrowManager grow_manager;
SensorManager sensor_manager;

void setup()
{
  delay(200);
  Serial.begin(74880);

  Serial << endl << endl <<
  Serial << "==============================================================================" << endl;
  Serial << "                               Welcome to NodeOS!" << endl;
  Serial << "==============================================================================" << endl;

  Homie.setLedPin(HOMIE_STATUS_PIN, LOW);
  // test_led.setMode(4);
  	Homie_setFirmware("node-os", "1.0.0"); // The "_" is not a typo! See Magic bytes
    Homie_setBrand("Grow Nodes"); // before Homie.setup()

    ntp_manager.setup();
    sensor_manager.setup();

    Homie.setup();


}

void loop()
{
    ntp_manager.loop();
    if (Homie.isConnected()) {
      sensor_manager.loop();
      grow_manager.loop(sensor_manager.getAirTempF());
    }

    Homie.loop();
}
