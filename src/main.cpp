#include "Arduino.h"
#include "../lib/containers/InternetManager/InternetManager.cpp"
// #include "../lib/components/Led/Led.cpp"

// D0 = NodeMCU LED
// D4 = ESP8266 LED

InternetManager internetManager;

Led test_led(D0);

void setup()
{
  Serial.begin(9600);
  Serial.print("\n\n==============================================================================\n");
  Serial.print("                               Welcome to NodeOS!\n");
  Serial.print("==============================================================================\n\n");

  test_led.setMode(4);
  internetManager.setup();
}

void loop()
{
  test_led.update();
  internetManager.loop();
}
