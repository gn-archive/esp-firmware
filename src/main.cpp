#include <main.h>

GrowProgram grow_program;
Shifty ShiftReg;

void onSystemEvent(const HomieEvent& event) {
  switch(event.type) {
    case HomieEventType::MQTT_CONNECTED:
      grow_program.uploadCurrentState();
      Sensors.uploadCurrentState();
    break;
  }
}


void setup()
{
  ShiftReg.setBitCount(8);
  // data, clock, latch
  ShiftReg.setPins(SHIFT_DATA_PIN, SHIFT_CLOCK_PIN, SHIFT_LATCH_PIN);
  // All outputs default to low

  delay(200);
  Serial.begin(74880);

  Homie.disableLogging(); // before Homie.setup()
  Serial.println(F("=============================================================================="));
  Serial.println(F("                               Welcome to NodeOS!"));
  Serial.println(F("=============================================================================="));

  Homie.setLedPin(HOMIE_STATUS_PIN, LOW);
  Homie_setFirmware("node-os", "0.0.14"); // The "_" is not a typo! See Magic bytes
  Homie_setBrand("Grow Nodes"); // before Homie.setup()
  Homie.onEvent(onSystemEvent);

  Homie.setup();

  System.setup();
  Sensors.setup();
  grow_program.setup();

}

void loop()
{
    Homie.loop();

    System.loop();
    Sensors.loop();
    grow_program.loop();
}
