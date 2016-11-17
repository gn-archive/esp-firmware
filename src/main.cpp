#include "Arduino.h"
#include "../lib/containers/InternetManager/InternetManager.cpp"
// #include "../lib/components/Led/Led.cpp"

// D0 = NodeMCU LED
// D4 = ESP8266 LED

InternetManager internetManager;

// Led test_led(D0);

void setup()
{
  Serial.begin(9600);

  // test_led.setMode(3);
  internetManager.setup();
}

void loop()
{
  // test_led.update();
  internetManager.loop();
}
