#include "Arduino.h"
#include "../lib/Led/Led.cpp"


Led led1(D0);

void setup()
{
  Serial.begin(9600);
}

void loop()
{
    if (Serial.available()) {
    int setmode = Serial.read() - 48;
    led1.setMode(setmode);
    Serial.print(setmode);
    }

	led1.update();
}
