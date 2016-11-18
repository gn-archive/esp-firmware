#include "Arduino.h"

#include <Homie.h>
#include <HomieManager.cpp>
// #include <Led.cpp>
// D0 = NodeMCU LED
// D4 = ESP8266 LED

// Led test_led(D0);

HomieManager homie_manager;


void setup()
{
  delay(200);
  Serial.begin(74880);

  Homie.setLedPin(D0, LOW);
  Serial << endl << endl <<
  Serial << "==============================================================================" << endl;
  Serial << "                               Welcome to NodeOS!" << endl;
  Serial << "==============================================================================" << endl;

  // test_led.setMode(4);
  	Homie_setFirmware("node-os", "1.0.0"); // The "_" is not a typo! See Magic bytes
    Homie_setBrand("Grow Nodes"); // before Homie.setup()

  	Homie.setup();
    homie_manager.setup();
}

void loop()
{
  homie_manager.loop();
  Homie.loop();
  // config_svc.loop();
  // test_led.update();
}
