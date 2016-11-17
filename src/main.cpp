#include "Arduino.h"
#include "../lib/Led/Led.cpp"


Led led1(D0);

void setup()
{
  Serial.begin(9600);
}

void loop()
{

    led1.setMode(4);

	led1.update();
}
