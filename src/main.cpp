#include <main.h>

GrowProgram grow_program;

void onSystemEvent(const HomieEvent& event) {
  switch(event.type) {
    case HomieEventType::MQTT_CONNECTED:
      grow_program.uploadCurrentState();
      System.uploadCurrentState();
    break;
  }
}


void setup()
{
  delay(200);
  Serial.begin(74880);

  Homie.getLogger() << endl << endl;
  Homie.getLogger() << F("==============================================================================") << endl;
  Homie.getLogger() << F("                               Welcome to NodeOS!") << endl;
  Homie.getLogger() << F("==============================================================================") << endl;

  Homie.setLedPin(HOMIE_STATUS_PIN, LOW);
  Homie_setFirmware("node-os", "1.0.0"); // The "_" is not a typo! See Magic bytes
  Homie_setBrand("Grow Nodes"); // before Homie.setup()
  Homie.onEvent(onSystemEvent);

  Homie.setup();

  System.setup();
  grow_program.setup();

}

void loop()
{
    Homie.loop();

    System.loop();
    grow_program.loop();
}
