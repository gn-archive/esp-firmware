#include "Arduino.h"

#include <Homie.h>
#include <SystemManager.hpp>
// #include <Led.cpp>
// D0 = NodeMCU LED
// D4 = ESP8266 LED

// Led test_led(D0);

SystemManager system_manager;


void setup()
{
  delay(200);
  Serial.begin(74880);

  Serial << endl << endl <<
  Serial << "==============================================================================" << endl;
  Serial << "                               Welcome to NodeOS!" << endl;
  Serial << "==============================================================================" << endl;

  Homie.setLedPin(D0, LOW);
  // test_led.setMode(4);
  	Homie_setFirmware("node-os", "1.0.0"); // The "_" is not a typo! See Magic bytes
    Homie_setBrand("Grow Nodes"); // before Homie.setup()

  	Homie.setup();
    system_manager.setup();
}

void loop()
{
  system_manager.loop();
  Homie.loop();
  // config_svc.loop();
  // test_led.update();
}
